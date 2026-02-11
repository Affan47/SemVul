str_escape(const char *str, const char div, const char mask)
{
  const int len = strlen(str);
  int buflen = (2 * len), blen = 0;
  char *buf = nmalloc(buflen + 1), *b = buf;
  const char *s;

  if (!buf)
    return NULL;
  for (s = str; *s; s++) {

    if ((buflen - blen) <= 3) {
      buflen = (buflen * 2);
      buf = nrealloc(buf, buflen + 1);
      if (!buf)
        return NULL;
      b = buf + blen;
    }

    if (*s == div || *s == mask) {
      sprintf(b, "%c%02x", mask, *s);
      b += 3;
      blen += 3;
    } else {
      *(b++) = *s;
      blen++;
    }
  }
  *b = 0;
  return buf;
}
