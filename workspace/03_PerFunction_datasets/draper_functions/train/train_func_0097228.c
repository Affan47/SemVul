my_wc_mb_euc_kr(CHARSET_INFO *cs __attribute__((unused)),
		 my_wc_t wc, uchar *s, uchar *e)
{
  int code;

  if (s >= e)
    return MY_CS_TOOSMALL;

  if ((uint) wc < 0x80)
  {
    s[0]= (uchar) wc;
    return 1;
  }

  if (!(code=func_uni_ksc5601_onechar(wc)))
    return MY_CS_ILUNI;

  if (s+2>e)
    return MY_CS_TOOSMALL2;

  s[0]=code>>8;
  s[1]=code&0xFF;

  return 2;
}
