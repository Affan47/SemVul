_GAEncodeBase(unsigned int base, unsigned BITBASE val,
	      GABit * binstr, int n, int c)
{
  int status = 0;
  if(c < 0) return 1;

  unsigned BITBASE modval = val % base;
  binstr[c] = STA_CAST(GABit,modval);
  unsigned BITBASE quotient = val / base;
  if(quotient) status = _GAEncodeBase(base, quotient, binstr, n, c-1);
  return status;
}
