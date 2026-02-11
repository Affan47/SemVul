removeFrameReference(unsigned long frame, unsigned long numberOfFrames)
{
  unsigned long i;
  char str[20];
  OFString aString;

  updateCache();
  referencedFrameNumber.clear();
  if (frameCache)
  {
    for (i=0; i<frameCacheEntries; i++)
    {
      if (frameCache[i] != (Sint32)frame)
      {
      	if (aString.size() ==0) sprintf(str, "%ld", (long)(frameCache[i])); else sprintf(str, "\\%ld", (long)(frameCache[i]));
      	aString += str;
      }
    }
  } else {
    for (i=1; i<=numberOfFrames; i++)
    {
      if (i != frame)
      {
      	if (aString.size() ==0) sprintf(str, "%ld", i); else sprintf(str, "\\%ld", i);
      	aString += str;
      }
    }
  }
  referencedFrameNumber.putString(aString.c_str());
  flushCache();
}
