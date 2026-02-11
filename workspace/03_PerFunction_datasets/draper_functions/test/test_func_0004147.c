my_strnncollsp_ucs2_bin(CHARSET_INFO *cs __attribute__((unused)),
                                   const uchar *s, size_t slen,
                                   const uchar *t, size_t tlen,
                                   my_bool diff_if_only_endspace_difference
                                   __attribute__((unused)))
{
  const uchar *se, *te;
  size_t minlen;


  slen= (slen >> 1) << 1;
  tlen= (tlen >> 1) << 1;

  se= s + slen;
  te= t + tlen;

  for (minlen= min(slen, tlen); minlen; minlen-= 2)
  {
    int s_wc= s[0] * 256 + s[1];
    int t_wc= t[0] * 256 + t[1];
    if ( s_wc != t_wc )
      return  s_wc > t_wc ? 1 : -1;

    s+= 2;
    t+= 2;
  }

  if (slen != tlen)
  {
    int swap= 1;
    if (slen < tlen)
    {
      s= t;
      se= te;
      swap= -1;
    }

    for ( ; s < se ; s+= 2)
    {
      if (s[0] || s[1] != ' ')
        return (s[0] == 0 && s[1] < ' ') ? -swap : swap;
    }
  }
  return 0;
}
