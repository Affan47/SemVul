printTraced(Trace *pTrace, unsigned int tbi,
					char *pBuf, int szBuf)

{
  if (!pBuf || !pTrace)
    return 0;

  int m;

  if (bHasExpression()) {
    char buf[256];
    printExpression(buf, sizeof(buf));
    m = snprintf(pBuf, szBuf,
		 " assertion at 0x%04x, expr:%s",address,buf);
  } else
    m = snprintf(pBuf, szBuf,
		 " execution at 0x%04x",address);

  return m>0 ? m : 0;
}
