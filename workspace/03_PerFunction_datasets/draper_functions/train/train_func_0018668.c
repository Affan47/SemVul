unicodeToString(char *p, size_t len)
  {
  size_t i;
  static char *buf;
  static size_t bufsiz;

  allocbuf(buf, bufsiz, len + 1, char *);

  for (i=0; i<len; ++i)
    {
    buf[i] = *p & 0x7f;
    p += 2;
    }

  buf[i] = '\0';
  return buf;
  }
