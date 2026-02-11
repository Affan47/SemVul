tiltSlew(double deg)
{
  if (deg > getMaxTiltSlew())
    deg = getMaxTiltSlew();
  if (deg < getMinTiltSlew())
    deg = getMinTiltSlew();

  myTiltSlew = deg;
  preparePacket();
  myPacket.byteToBuf('T');
  myPacket.byteToBuf('S');

  myPacket.byte2ToBuf(ArMath::roundInt(deg/myTiltConvert));

  return sendPacket(&myPacket);
}
