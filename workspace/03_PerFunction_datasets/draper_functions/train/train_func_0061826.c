gstrsub(const char *s, const char *search, const char *replace)
{
  int ooffs = 0;
  char *o, *c;
  char *src = (char *)s;
  int olen = strlen(src);
  int slen = strlen(search);
  int rlen = strlen(replace);

  o = (char *) xmalloc(olen + 1);

  while ((c = strstr(src, search))) {
    olen += (rlen - slen);
    o = (char *) xrealloc(o, olen + 1);
    memcpy(o + ooffs, src, c - src);
    ooffs += (c - src);
    src = c + slen;
    if (rlen) {
      memcpy(o + ooffs, replace, rlen);
      ooffs += rlen;
    }
  }

  if (ooffs < olen) {
    memcpy(o + ooffs, src, olen - ooffs);
  }
  o[olen] = '\0';
  return o;
}
