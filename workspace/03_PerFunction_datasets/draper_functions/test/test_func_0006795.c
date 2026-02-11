vsnprintf_wrap(const char *format, va_list v)
{
  va_list w;

  va_copy(w,v);;
  char *str = NULL;
  int plen = 0;

  plen = vsnprintf(str, 0, format, v);

  if (plen > 0) {
    str = (char *)malloc(plen+1);
    if (str) {
      (void)vsnprintf(str, plen+1, format, w);
      va_end(w);
    }
  }

  return str;
}
