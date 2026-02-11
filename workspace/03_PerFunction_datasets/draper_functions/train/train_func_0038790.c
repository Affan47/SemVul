my_mb_ctype_mb(CHARSET_INFO *cs, int *ctype,
                   const uchar *s, const uchar *e)
{
  my_wc_t wc;
  int res= cs->cset->mb_wc(cs, &wc, s, e);
  if (res <= 0 || wc > 0xFFFF)
    *ctype= 0;
  else
    *ctype= my_uni_ctype[wc>>8].ctype ?
            my_uni_ctype[wc>>8].ctype[wc&0xFF] :
            my_uni_ctype[wc>>8].pctype;
  return res;
}
