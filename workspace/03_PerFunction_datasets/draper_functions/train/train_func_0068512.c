my_casedn_utf32(CHARSET_INFO *cs, char *src, size_t srclen,
                char *dst __attribute__((unused)),
                size_t dstlen __attribute__((unused)))
{
  my_wc_t wc;
  int res;
  char *srcend= src + srclen;
  MY_UNICASE_INFO **uni_plane= cs->caseinfo;
  DBUG_ASSERT(src == dst && srclen == dstlen);

  while ((res= my_utf32_uni(cs, &wc, (uchar*) src, (uchar*) srcend)) > 0)
  {
    my_tolower_utf32(uni_plane,&wc);
    if (res != my_uni_utf32(cs, wc, (uchar*) src, (uchar*) srcend))
      break;
    src+= res;
  }
  return srclen;
}
