ull2dec(ulonglong from, decimal_t *to)
{
  int intg1, error=E_DEC_OK;
  ulonglong x=from;
  dec1 *buf;

  sanity(to);

  for (intg1=1; from >= DIG_BASE; intg1++, from/=DIG_BASE) ;
  if (unlikely(intg1 > to->len))
  {
    intg1=to->len;
    error=E_DEC_OVERFLOW;
  }
  to->frac=0;
  to->intg=intg1*DIG_PER_DEC1;

  for (buf=to->buf+intg1; intg1; intg1--)
  {
    ulonglong y=x/DIG_BASE;
    *--buf=(dec1)(x-y*DIG_BASE);
    x=y;
  }
  return error;
}
