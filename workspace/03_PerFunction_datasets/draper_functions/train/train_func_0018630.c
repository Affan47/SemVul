comDataN(unsigned char command, const char* data, int size)
{
  if(!connValid()) return false;
  if(size > 200) return false;

  bool ret = true;

  mySendingMutex.lock();

  myPacket.empty();
  myPacket.setID(command);
  myPacket.uByteToBuf(STRARG);
  myPacket.strNToBuf(data, size);
  myPacket.finalizePacket();

  ret = (myDeviceConn->write(myPacket.getBuf(), myPacket.getLength()) >= 0);

  if (myPacketSentCallback != NULL)
    myPacketSentCallback->invoke(&myPacket);

  mySendingMutex.unlock();

  return ret;
}
