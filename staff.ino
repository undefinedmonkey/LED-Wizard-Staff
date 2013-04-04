typedef void (* fnPointer)(int pin, int *intensity);

/**
 *  ___1___ 
 * |   ^   |
 * 4   *   2
 * |       |
 *  ---3---
 *
 * Each function controls a face. Faces don't have action queues.
 * They have a function that's called every step which updates
 * its intensity. To change face behavior, reassign the function pointer. 
 */
fnPointer facePointer[4];
int intensities[4] = {0, 0, 0, 0};
int inputs[4] = {0, 0, 0, 0};
int counter = 0;

void setup()  { 
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  facePointer[0] = randomizer;
  facePointer[1] = randomizer;
  facePointer[2] = randomizer;
  facePointer[3] = randomizer;
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
} 

void loop()  {

  if (counter++ == 2000) {
    facePointer[0] = fadeUp;
    facePointer[1] = fadeDown; 
    facePointer[2] = fadeUp;
    facePointer[3] = fadeDown; 
  }
  else if (counter == 4000) {
    facePointer[0] = randomizer;
    facePointer[1] = randomizer;
    facePointer[2] = randomizer;
    facePointer[3] = randomizer;
    counter = 0;
  }
  
  for (int i = 0; i < 4; i++) {
    facePointer[i](retPin(i), &intensities[i]);
  }  
 
  // wait for 30 milliseconds to see the dimming effect    
  delay(50);                            
}

void fadeDown(int pin, int *intensity) {

  analogWrite(pin, *intensity);
  
  *intensity += 5;
  
  if (*intensity >= 255) {
    *intensity = 0; 
  }
}

void fadeUp(int pin, int *intensity) {

  analogWrite(pin, *intensity);
  
  *intensity -= 5;
  
  if (*intensity <= 0) {
    *intensity = 255; 
  }
}

void heavyBlinker(int pin, int *intensity) {

  analogWrite(pin, *intensity);
  
  if (*intensity >= 127) {
    *intensity = 0; 
  }
  else {
    *intensity = 255; 
  }
}

void minimalBlinker(int pin, int *intensity) {

  analogWrite(pin, *intensity);
  
  if (*intensity >= 127) {
    *intensity = 0; 
  }
  else {
    *intensity = 127; 
  }
}

void steadyOn(int pin, int *intensity) {
  analogWrite(pin, *intensity);
  *intensity = 0;
}

void steadyOff(int pin, int *intensity) {
  analogWrite(pin, *intensity);
  *intensity = 255;
}

void pulse(int pin, int *intensity) {
  if (*intensity == 0) {
   
  }
  else if (*intensity == 255) {
   
  } 
}

void randomizer(int pin, int *intensity) {
  analogWrite(pin, random(1, 255)); 
}

int retPin(int num) {
  int pin;
  switch (num) {
    case 0:
      pin = 6;
      break;
    case 1:
      pin = 9;
      break;
    case 2:
      pin = 10;
      break;
    case 3:
      pin = 11;
      break;
    default:
      pin = 6;
      break;
  } 
  
  return pin;
}
