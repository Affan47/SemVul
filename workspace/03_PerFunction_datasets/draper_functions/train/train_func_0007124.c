strToUnicode(char *p)
  {
  static unsigned char *buf;
  static size_t bufsiz;
  size_t l = strlen(p);
  int i = 0;

  allocbuf(buf, bufsiz, l * 2, unsigned char *);

  while (l--)
    {
    buf[i++] = *p++;
    buf[i++] = 0;
    }

  return buf;
  }
