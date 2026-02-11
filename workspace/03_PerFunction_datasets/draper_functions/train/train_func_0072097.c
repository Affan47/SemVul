dc_initinversesuftabnonspecials(GtDifferencecover *dcov)
{
  unsigned long sampleindex, pos;

  for (sampleindex=0; sampleindex < dcov->effectivesamplesize; sampleindex++)
  {
    pos = dc_suffixptrget(dcov,sampleindex);
    dc_inversesuftab_set(dcov,pos,sampleindex);
  }
}
