egg_strcatn(char *dst, const char *src, size_t max)
{
  size_t tmpmax = 0;


  while (*dst && max > 0) {
    dst++;
    max--;
  }


  tmpmax = max;


  while (*src && max > 1) {
    *dst++ = *src++;
    max--;
  }


  *dst = 0;


  return tmpmax - max;
}
