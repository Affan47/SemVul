handleJoystickPacket(ArRobotPacket *packet)
{

  if (packet->getID() != 0xF8)
    return false;

  myDataReceived.setToNow();

  if (packet->bufToUByte() != 0)
    myButton1 = true;
  else
    myButton1 = false;

  if (packet->bufToUByte() != 0)
    myButton2 = true;
  else
    myButton2  = false;


  myJoyX = -((double)packet->bufToUByte2() - 512.0) / 512.0;
  myJoyY = ((double)packet->bufToUByte2() - 512.0) / 512.0;

  myThrottle = (double)packet->bufToUByte2() / 1024.0;


  if (!myGotData)
  {
    ArLog::log(ArLog::Verbose, "Received joystick information from the robot");
    myGotData = true;
  }
  return true;
}
