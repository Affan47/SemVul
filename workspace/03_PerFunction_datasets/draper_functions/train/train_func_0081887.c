handleJoystickPacket(
	ArRobotPacket *packet)
{
  if (packet->getID() != 0xF8)
    return false;

  myPacketReceivedTime.setToNow();

  myButton1 = packet->bufToUByte();
  myButton2 = packet->bufToUByte();
  myJoyX = packet->bufToUByte2();
  myJoyY = packet->bufToUByte2();
  myThrottle = packet->bufToUByte2();


  return true;
}
