getTargetMaxPDU(const char *targetID)
{
  const char *c = getConfigEntry(L2_COMMUNICATION, targetID, L0_MAXPDU);
  unsigned long result = 0;
  if (c)
  {
    if (1 != sscanf(c, "%lu", &result)) result=0;
  }
  return result;
}
