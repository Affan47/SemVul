utf8_str_eq(char *a, char *b, int len)
{
  int ta = utf8_tlen(a, len);
  int tb = utf8_tlen(b, len);

  if (ta != tb)
    return FALSE;

  return !memcmp(a, b, ta);
}
