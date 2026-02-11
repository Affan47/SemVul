GetCharSetName()
{
  if (mDetectedCharset)
    return mDetectedCharset;
  switch (mInputState)
  {
  case eHighbyte:
    {
      float proberConfidence;
      float maxProberConfidence = (float)0.0;
      int maxProber = 0;

      for (int i = 0; i < NUM_OF_CHARSET_PROBERS; i++)
      {
        proberConfidence = mCharSetProbers[i]->GetConfidence();
        if (proberConfidence > maxProberConfidence)
        {
          maxProberConfidence = proberConfidence;
          maxProber = i;
        }
      }

      if (maxProberConfidence > MINIMUM_THRESHOLD)
        return mCharSetProbers[maxProber]->GetCharSetName();
    }
  case eEscAscii:
    break;
  default:
      ;
  }
  return "UTF-8";

}
