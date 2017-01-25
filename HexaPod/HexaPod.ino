// Tibia <- Femur <- Coxa
// FL - 1,2,3
// ML - 4,5,6
// BL - 9,10,11

// FR - 24,23,22
// MR - 21,20,19
// BR - 16,15,14

#define BUTTON 2
#define JOISTICK_HORIZONTAL A0
#define JOISTICK_VERTICAL A1

#define DEFAULT_SPEED 1000

//#define DEBUG

#ifdef DEBUG
#define UP_STATE test1
#define DOWN_STATE test2
#else
#define UP_STATE standup
#define DOWN_STATE sitdown
#endif

bool ready = false; // sit down; read = true -- stood up
bool buttonWasPushed = false;

void sitdown(int speed) {
  //RightDown
  Serial.print("#23P1500#5P1500#15P1500T");
  Serial.println(speed);
  delay(speed);
  //LeftUP
  Serial.print("#2P2400#20P2400#10P2400T");
  Serial.println(speed);
  delay(speed);
}

void standup(int speed) {
  //LeftDown
  Serial.print("#2P1500#20P1500#10P1500T");
  Serial.println(speed);
  delay(speed);
  //Right UP
  Serial.print("#23P2400#5P2400#15P2400T");
  Serial.println(speed);
  delay(speed);
}


void test1(int speed) { //Left UP
  // Left
  Serial.print("#1P1500#2P2500#3P1500#4P1500#5P1500#6P1500#9P1500#10P2500#11P1500");
  // Right
  Serial.print("#24P1500#23P1500#22P1500#21P1500#20P2500#19P1500#16P1500#15P1500#14P1500T");
  Serial.println(speed);
  delay(speed);
}

void test2(int speed) { //Right UP
  // Left
  Serial.print("#1P1500#2P1500#3P1500#4P1500#5P2500#6P1500#9P1500#10P1500#11P1500");
  // Right
  Serial.print("#24P1500#23P2500#22P1500#21P1500#20P1500#19P1500#16P1500#15P2500#14P1500T");
  Serial.println(speed);
  delay(speed);
}

// triangle left -- Left-Front, Left-Back, Right-Middle
void tleft_forward(int speed) {
  Serial.print("#3P1700#11P1700#19P1400T");
  Serial.println(speed);
  delay(speed);
}

// triangle left -- Left-Front, Left-Back, Right-Middle
void tleft_back(int speed) {
  Serial.print("#3P1400#11P1400#19P1700T");
  Serial.println(speed);
  delay(speed);
}

// triangle right -- Left-Middle, Right-Front, Right-Back
void tright_forward(int speed) {
  Serial.print("#22P1400#14P1400#6P1700T");
  Serial.println(speed);
  delay(speed);
}

// triangle right -- Left-Middle, Right-Front, Right-Back
void tright_back(int speed) {
  Serial.print("#22P1700#14P1700#6P1400T");
  Serial.println(speed);
  delay(speed);
}


void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(JOISTICK_HORIZONTAL, INPUT);
  pinMode(JOISTICK_VERTICAL, INPUT);

  Serial.begin(9600);
  Serial.println("Start");
  Serial.print("#1P1500#2P1500#3P1500#4P1500#5P1500#6P1500#9P1500#10P1500#11P1500#14P1500#15P1500#16P1500#19P1500#20P1500#21P1500#22P1500#23P1500#24P1500T");
  delay(500);
  sitdown(DEFAULT_SPEED);
}

void swapState() {
  ready = !ready;
  if (ready) {
    Serial.println("UP");
    UP_STATE(DEFAULT_SPEED); // Right triangle up
    tleft_back(DEFAULT_SPEED);
    tright_forward(DEFAULT_SPEED);
  }
  else {
    Serial.println("DOWN");
    DOWN_STATE(DEFAULT_SPEED); // Left triangle up
    tright_back(DEFAULT_SPEED);
    tleft_forward(DEFAULT_SPEED);
  }
}

void checkButton() {
  bool buttonPushedNow = digitalRead(BUTTON) == LOW;
  delay(50);
  if (buttonPushedNow && !buttonWasPushed) {
    buttonPushedNow = digitalRead(BUTTON) == LOW;
    if (buttonPushedNow) {
      swapState();
    }
  }
  buttonWasPushed = buttonPushedNow;
}

void loop() {
  checkButton();

}

