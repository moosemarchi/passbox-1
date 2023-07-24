#include <Keypad.h>
#include <Servo.h>

const int ROW_NUM = 4; // Number of rows on the keypad
const int COLUMN_NUM = 4; // Number of columns on the keypad



char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};       // Connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
Servo servo;

const char* correctPassword = "1134"; // Replace with your desired password

char passwordBuffer[5];
int currentIndex = 0;

void setup() {
  servo.attach(13); // Connect the servo signal wire to digital pin D2
  servo.write(0);  // Set the initial position of the servo to 0 degrees (closed position)
  Serial.begin(9600);
  pinMode(12, OUTPUT);
pinMode(11, OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    checkPassword(key);
  }
}

void checkPassword(char key) {
   if (key == '*');
   servo.write(0);
  
  if (key == '#') { // Enter key pressed
    passwordBuffer[currentIndex] = '\0'; // Null-terminate the password buffer
    currentIndex = 0;
    if (strcmp(passwordBuffer, correctPassword) == 0) {
      Serial.println("Correct password entered");
       digitalWrite(11, HIGH);
      delay(1000);
      digitalWrite(11, LOW);
      rotateServo();
     
    } else {
      Serial.println("Incorrect password");
      digitalWrite(12, HIGH);
      delay(1000);
      digitalWrite(12, LOW);
    }
    clearPasswordBuffer();
  } else if (key == '*') { // Clear key pressed
    clearPasswordBuffer();
  } else {
    if (currentIndex < 4) {
      passwordBuffer[currentIndex] = key;
      currentIndex++;
    }
  }
}

void clearPasswordBuffer() {
  for (int i = 0; i < 5; i++) {
    passwordBuffer[i] = '\0';
  }
  currentIndex = 0;
}

void rotateServo() {
  servo.write(135); // Rotate the servo to 90 degrees (open position)
}
