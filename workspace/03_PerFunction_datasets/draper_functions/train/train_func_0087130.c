strip_separator_vbar(char *buf, const char *str)
{
  const char *src = str;
  char *dst = buf;
  while (*src) {
    if (*src != '|' && *src != '~') {
      *dst = *src;
      dst ++;
    }
    src ++;
  }
  *dst = 0;
}
