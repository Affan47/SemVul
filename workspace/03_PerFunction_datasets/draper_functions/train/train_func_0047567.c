byte2ToBuf(ArTypes::Byte2 val)
{
  if ((myLength + 2) > myMaxLength)
  {
    ArLog::log(ArLog::Terse, "ArAMPTUPacket::Byte2ToBuf: Trying to add beyond length of buffer.");
    return;
  }
  myBuf[myLength] = val/255;
  ++myLength;
  myBuf[myLength] = val%255;
  ++myLength;
}
