/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include <iostream>
#include <cstring>
#include "Leap.h"
#include <unistd.h>

using namespace Leap;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
 usleep(500000); // Sleep for a half second
 const Frame frame = controller.frame();
/*  std::cout << "Frame id: " << frame.id()
            << ", timestamp: " << frame.timestamp()
            << ", hands: " << frame.hands().count()
            << ", extended fingers: " << frame.fingers().extended().count()
            << ", tools: " << frame.tools().count()
            << ", gestures: " << frame.gestures().count() << std::endl;
*/
  HandList hands = frame.hands();
  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    // Get the first hand
    const Hand hand = *hl;
    std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
//    std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
//              << ", palm position: " << hand.palmPosition() << std::endl;
    // Get the hand's normal vector and direction
//    const Vector normal = hand.palmNormal();
//    const Vector direction = hand.direction();

    // Calculate the hand's pitch, roll, and yaw angles
//    std::cout << std::string(2, ' ') <<  "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
//              << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
//              << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;

    // Get fingers
	Vector test = Vector::zero();
	Vector check = Vector::zero();
	float dir [5];
	int count = 0;
    const FingerList fingers = hand.fingers();
    for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
      const Finger finger = *fl;

      // Get finger bones
      for (int b = 2; b < 3; ++b) {
        Bone::Type boneType = static_cast<Bone::Type>(b);
        Bone bone = finger.bone(boneType);
//        std::cout << std::string(6, ' ') <<  boneNames[boneType]
//                  << " bone, start: " << bone.prevJoint()
//                  << ", end: " << bone.nextJoint()
//                  << ", direction: " << bone.direction() << std::endl;
	test += bone.direction();
	check = bone.direction();
	dir[count] = check.z;
	
	std::cout<<"finger type "<<finger.type()<<" "<<check.z<<std::endl;
		

	}
	check = Vector::zero();
	count ++;
    }
//	std::cout << test.z << std::endl; //TODO FIND OUT HOW TO ROTATE VALES TO MAKE HAND UP PROPERLY
	//testmethod(test);
	if(isS(dir)){
	std::cout << "IT IS S" << std::endl;
	std::system("espeak -s 10 'It is S'");
	}
	
	else if(isA(dir)){
	std::cout << "IT IS A" << std::endl;
	std::system("espeak -s 10 'It is A'");
  
	}
	else if(isE(dir)){
	std::cout<<"IT IS E"<<std::endl;	
	std::system("espeak -s 10 'It is E'");
	}
	else if(isT(dir)){
	std::cout<<"IT IS T"<<std::endl;
	std::system("espeak -s 10 'It is T'");	
	}
	else if(isX(dir)){
	std::cout<<"IT IS X"<<std::endl;
	std::system("espeak -s 10 'It is X'");	
	}
	test = Vector::zero();
  }
}

bool isE(float dir[5]){
	bool check=false;
		if(dir[0]>=0.22 && dir[0]<0.40 && dir[1]<-0.20 && dir[1]>-0.35 && dir[4]<-0.05 && dir[4]>-0.15)
	{
		check=true;
	}
	return check;	
}
bool isX(float dir[5]){
	bool check=false;
		if(dir[0]>=0.65 && dir[0]<0.89 && dir[1]>=0.38 && dir[1]<0.49 && dir[4]<-0.75 && dir[4]>-1.0)
	{
		check=true;
	}
	return check;	
}
bool isS(float dir[5]){
	bool check=false;
		if(dir[0]>0.65 && dir[0]<0.89 && dir[1]<-0.85 && dir[1]>-1.0 && dir[4]<-0.75 && dir[4]>-1.0)
	{
		check=true;
	}
	return check;	
}
bool isA(float dir[5]){
	bool check=false;
	if(dir[0]>=0.89 && dir[0]<1.0 && dir[1]<-0.85 && dir[1]>-1.0 && dir[4]<-0.75 && dir[4]>-1.0)
	{
	check=true;

	}
	return check;
	}


bool isT(float dir[5]){
	bool check=false;
	if(dir[0]>=0.89 && dir[0]<1.0 && dir[1]<-0.85 && dir[1]>-1.0 && dir[4]<-0.75 && dir[4]>-1.0)
	{
	check=true;

	}
	return check;
	}


void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}

int main(int argc, char** argv) {
  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
