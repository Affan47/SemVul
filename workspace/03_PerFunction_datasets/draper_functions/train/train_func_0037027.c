hashcode(const char *s)
{
  long h = 0x1013;
  while (*s)
    {
      h = (h<<6) | ((h&0xfc000000)>>26);
      h ^= (*s);
      s++;
    }
  return h;
}
