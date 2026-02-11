removeFrameReference(const char *sopinstanceuid, unsigned long frame, unsigned long numberOfFrames)
{
  if ((frame<1)||(numberOfFrames<frame)) return;
  OFListIterator(DVPSReferencedImage *) first = list_.begin();
  OFListIterator(DVPSReferencedImage *) last = list_.end();
  while (first != last)
  {
    if ((*first)->isSOPInstanceUID(sopinstanceuid))
    {
      (*first)->removeFrameReference(frame, numberOfFrames);
      if ((*first)->appliesToAllFrames())
      {
        delete (*first);
        first = list_.erase(first);
      } else ++first;
    } else ++first;
  }
  return;
}
