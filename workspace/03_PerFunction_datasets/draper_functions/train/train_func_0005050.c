handleSimStatPacket(ArRobotPacket *pkt)
{
  if(pkt->getID() != 0x62) return false;
  char c = pkt->bufToByte();
  c = pkt->bufToByte();
  ArTypes::UByte4 flags = pkt->bufToUByte4();
  if(flags&ArUtil::BIT1)
  {
    myData.timeGotPosition.setToNow();
    myData.fixType = SimulatedFix;
    myData.HDOP = myData.VDOP = myData.PDOP = 1.0;
    myData.haveHDOP = myData.haveVDOP = myData.havePDOP = true;

    myData.numSatellitesTracked = 0;
    int x = pkt->bufToUByte2();
    x = pkt->bufToUByte2();
    x = pkt->bufToUByte2();
    x = pkt->bufToByte4();
    x = pkt->bufToByte4();
    x = pkt->bufToByte4();
    x = pkt->bufToByte4();

    myData.havePosition = true;
    myData.latitude = pkt->bufToByte4() / 10e6;
    myData.longitude = pkt->bufToByte4() / 10e6;
    myData.GPSPositionTimestamp.setToNow();

    myData.haveAltitude = true;
    myData.altitude = pkt->bufToByte4() / 100.0;
  }
  else
  {
    if(myData.havePosition && !myHaveDummyPosition)
      clearPosition();
  }
  return true;
}
