init_ilogsum(void)
{
  static int firsttime = TRUE;
  if (!firsttime)  return;
  firsttime = FALSE;

  int i;
  for (i = 0; i < LOGSUM_TBL; i++)
    ilogsum_lookup[i] = rint(INTSCALE * (sreLOG2(1.+sreEXP2((double) -i/INTSCALE))));
}
