operator=(const ArRobotPacket &other)
{
  if (this != &other) {

    myHeaderLength = other.myHeaderLength;
    myFooterLength = other.myFooterLength;
    myReadLength   = other.myReadLength;
    myLength = other.myLength;
    mySync1 = other.mySync1;
    mySync2 = other.mySync2;
    myTimeReceived = other.myTimeReceived;

    if (myMaxLength != other.myMaxLength) {
      if (myOwnMyBuf && myBuf != NULL)
	delete [] myBuf;
      myOwnMyBuf = true;
      myBuf = NULL;
      if (other.myMaxLength > 0) {
        myBuf = new char[other.myMaxLength];
      }
      myMaxLength = other.myMaxLength;
    }

    if ((myBuf != NULL) && (other.myBuf != NULL)) {
      memcpy(myBuf, other.myBuf, myMaxLength);
    }

    myIsValid = other.myIsValid;
  }
  return *this;
}
