GetConfidence()
{

  if (mTotalRel > MINIMUM_DATA_THRESHOLD)
    return ((float)(mTotalRel - mRelSample[0]))/mTotalRel;
  else
    return (float)DONT_KNOW;
}
