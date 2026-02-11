appliesOnlyToFrame(unsigned long frame)
{
  Sint32 val=0;
  if (referencedFrameNumber.getVM() == 1)
  {
    if (EC_Normal == referencedFrameNumber.getSint32(val, 0))
    {
      if (frame == (unsigned long)val) return OFTrue;
    }
  }
  return OFFalse;
}
