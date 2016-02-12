/*
  Bean Car Example

  NOTE: This is an untested example and might have errors. I hope
  to test and improve this example in the future but I am providing 
  this as some people have been requesting it. 
  
  For use with the "Handy BLE" iPhone app by Paul Shelley and 
  the LightBlue Bean by Punchthrough Design.

  This sketch receives Serial data with a simple packet format
  of '#' for a start character and ';' as an end character. Start
  and end characters can be changed easily. Simple error checking 
  is also included. 
  
  Handy BLE - https://pdshelley.com
  LightBlueBean - https://punchthrough.com

  This example code is in the public domain.

  Created 11 Feb 2016
  by Paul Shelley
*/

String command;
boolean commandStarted = false;

/* 
Be sure to change these values to the pins you have your motors hooked 
up to if it is different than pin 1 and 2.
*/
int rightMotor = 1;
int leftMotor = 2;

void setup() {
  Serial.begin(57600);
  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);
}

void loop() {
  getCommand();
}

/* 
This function reads the serial port and checks for the start character '#'
if the start character if found it will add all received characters to 
the command buffer until it receives the end command ';' When the end 
command is received the commandCompleted() function is called.
if a second start character is found before an end character then the buffer
is cleared and the process starts over. 
*/
void getCommand() {
   while (Serial.available()) {
    char newChar = (char)Serial.read();
    if (newChar == '#') {
      commandStarted = true;
      command = "\0";
    } else if (newChar == ';') {
      commandStarted = false;
      commandCompleted();
      command = "\0";
    } else if (commandStarted == true) {
      command += newChar;
    }
  }
}

/*
This function takes the completed command and checks it against a list
of available commands and executes the appropriate code.  Add extra 'if' 
statements to add commands with the code you want to execute when that 
command is received. It is recommended to create a function for a command
if there are more than a few lines of code for as in the 'off' example.
*/
void commandCompleted() {
  if (command == "right") {
    digitalWrite(rightMotor, HIGH);
    Serial.print("Turning right motor");
  }
  if (command == "left") {
    digitalWrite(leftMotor, HIGH);
    Serial.print("Turning left motor");
  }
  if (command == "stopRight") {
    digitalWrite(rightMotor, LOW);
    Serial.print("Stop right motor");
  }
  if (command == "stopLeft") {
    digitalWrite(leftMotor, LOW);
    Serial.print("Stop left motor");
  }
  if (command == "go") {
    digitalWrite(rightMotor, HIGH);
    digitalWrite(leftMotor, HIGH);
    Serial.print("Go forward");
  }
  if (command == "stop") {
    stop();
  }
}

/*
Use a separate function like this when there are more than just a few
lines of code.  This will help maintain clean easy to read code.
*/
void stop() {
  digitalWrite(rightMotor, LOW);
  digitalWrite(leftMotor, LOW);
  Serial.print("Stop");
}
