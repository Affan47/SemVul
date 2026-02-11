setShorttag(Boolean b)
{
  for (int i = fSHORTTAG_FIRST; i <= fSHORTTAG_LAST; i++)
    booleanFeature_[i] = b;
  netEnable_ = netEnableAll;
}
