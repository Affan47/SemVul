my_uni_utf32(CHARSET_INFO *cs __attribute__((unused)),
             my_wc_t wc, uchar *s, uchar *e)
{
  if (s + 4 > e)
    return MY_CS_TOOSMALL4;

  s[0]= (uchar) (wc >> 24);
  s[1]= (uchar) (wc >> 16) & 0xFF;
  s[2]= (uchar) (wc >> 8)  & 0xFF;
  s[3]= (uchar) wc & 0xFF;
  return 4;
}
