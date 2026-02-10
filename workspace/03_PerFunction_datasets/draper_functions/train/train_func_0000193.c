TMX_TestStepOffset(void)
{
  struct timex txc;


  txc.modes = ADJ_MAXERROR;
  txc.maxerror = 0;
  if (adjtimex(&txc) < 0 || txc.maxerror != 0)
    return -1;

  txc.modes = ADJ_SETOFFSET;
  txc.time.tv_sec = 0;
  txc.time.tv_usec = 0;
  if (adjtimex(&txc) < 0 || txc.maxerror < 100000)
    return -1;

  return 0;
}
