panTilt_i(double degreesPan, double degreesTilt)
{
  if (degreesPan > getMaxPan())
    degreesPan = getMaxPan();
  if (degreesPan < getMinPan())
    degreesPan = getMinPan();
  myPan = degreesPan;

  if (degreesTilt > getMaxTilt())
    degreesTilt = getMaxTilt();
  if (degreesTilt < getMinTilt())
    degreesTilt = getMinTilt();
  myTilt = degreesTilt;

  myPanTiltPacket.byte2ToBufAtPos(ArMath::roundInt(myPan * myDegToPan), 6);
  myPanTiltPacket.byte2ToBufAtPos(ArMath::roundInt(myTilt * myDegToTilt), 10);
  return sendPacket(&myPanTiltPacket);
}
