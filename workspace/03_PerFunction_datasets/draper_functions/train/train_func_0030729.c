atScanStatus (statusStr)
     char *statusStr;
{
  int i;
  register char *strPtr;

  if (!(strcmp (statusStr, "P")))
    return (AF_PUBLISHED);

  strPtr = statusStr;
  while ((*strPtr = tolower (*strPtr))) strPtr++;

  for (i = 0; statusTable[i].name; i++)
    if (!(strcmp (statusStr, statusTable[i].name)))
      return (statusTable[i].code);

  return (AF_NOSTATE);
}
