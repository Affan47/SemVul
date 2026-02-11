WriteCriticalPackets(void)
{
  list<CriticalPacketEntry>::const_iterator packetentry = criticalpacketentries.begin();


  while (packetentry != criticalpacketentries.end())
  {

    if (!packetentry->WritePacket())
      return false;

    ++packetentry;
  }

  return true;
}
