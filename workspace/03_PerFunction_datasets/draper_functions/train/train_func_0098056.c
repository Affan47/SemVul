sendTiltSlew(void)
{
  char buf[4];

  if (myTiltSlewDesired > getMaxTiltSlew())
    myTiltSlewDesired = getMaxTiltSlew();
  if (myTiltSlewDesired < getMinTiltSlew())
    myTiltSlewDesired = getMinTiltSlew();

  if (myTiltSlewDesired != myTiltSlew)
  {
    ArLog::log(ArLog::Verbose,"ArVCC4::sendTiltSlew: sending tiltSlew packet");

    myPacket.empty();
    preparePacket(&myPacket);
    myPacket.uByteToBuf(ArVCC4Commands::TILTSLEW);

    sprintf(buf,"%3X", ArMath::roundInt(myTiltSlewDesired/.1125));

    if (buf[0] == ' ')
      buf[0] = '0';
    if (buf[1] == ' ')
      buf[1] = '0';

    myPacket.byteToBuf(buf[0]);
    myPacket.byteToBuf(buf[1]);
    myPacket.byteToBuf(buf[2]);

    requestBytes();
    myTiltSlewSent = myTiltSlewDesired;

    return sendPacket(&myPacket);
  }
  return true;
}
