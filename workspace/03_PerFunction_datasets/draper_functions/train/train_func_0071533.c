my_strnxfrm_unicode_full_bin(CHARSET_INFO *cs,
                             uchar *dst, size_t dstlen,
                             const uchar *src, size_t srclen)
{
  my_wc_t wc;
  uchar *de= dst + dstlen;
  uchar *de_beg= de - 2;
  const uchar *se = src + srclen;

  LINT_INIT(wc);
  DBUG_ASSERT(src);
  DBUG_ASSERT(cs->state & MY_CS_BINSORT);

  while (dst < de_beg)
  {
    int res;
    if ((res= cs->cset->mb_wc(cs, &wc, src, se)) <= 0)
      break;
    src+= res;
    *dst++= (uchar) (wc >> 16);
    *dst++= (uchar) ((wc >> 8) & 0xFF);
    *dst++= (uchar) (wc & 0xFF);
  }

  while (dst < de_beg)
  {
    *dst++= 0x00;
    *dst++= 0x00;
    *dst++= 0x20;
  }


  if (dst < de)
  {
    *dst++= 0x00;
    if (dst < de)
      *dst= 0x00;
  }

  return dstlen;
}
