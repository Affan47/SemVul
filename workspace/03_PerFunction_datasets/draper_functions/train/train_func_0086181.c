my_ucs2_uni(CHARSET_INFO *cs __attribute__((unused)),
		       my_wc_t * pwc, const uchar *s, const uchar *e)
{
  if (s+2 > e)
    return MY_CS_TOOSMALL2;

  *pwc= ((uchar)s[0]) * 256  + ((uchar)s[1]);
  return 2;
}
