sendDigitalZoom()
{
  ArLog::log(ArLog::Verbose,"ArVCC4::sendDigitalZoom: sending digital zoom packet");

  myPacket.empty();
  preparePacket(&myPacket);
  myPacket.uByteToBuf(ArVCC4Commands::DIGITALZOOM);

  if (myDigitalZoomDesired < 4)
  {
    myPacket.uByteToBuf(0x30);
    myPacket.uByteToBuf(0x30 + (0x1 << myDigitalZoomDesired));
  }
  else
  {


    myPacket.uByteToBuf(0x30);
    myPacket.uByteToBuf(0x3C);
  }

  requestBytes();
  return sendPacket(&myPacket);
}
