mpfr_sprintf (char *buf, const char *fmt, ...)
{
  char *str;
  int ret;

  GET_STR (ret, str, fmt);
  ret = sprintf (buf, "%s", str);

  mpfr_free_str (str);
  return ret;
}
