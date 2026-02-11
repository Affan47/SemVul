tiltSlew(double deg)
{
  if (deg > MAX_TILT_SLEW)
    deg = MAX_TILT_SLEW;
  if (deg < MIN_SLEW)
    deg = MIN_SLEW;

  myTiltSlew = deg;
  myPacket.empty();
  myPacket.byteToBuf(ArAMPTUCommands::TILTSLEW);
  myPacket.byteToBuf((int)(256 - (3840 / (float)deg)));
  return sendPacket(&myPacket);
}
