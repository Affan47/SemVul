parse_hex_color_channel(const char *s, int ndigits)
{
  int val1 = xvalue(s[0]);
  if (val1 < 0) return -1;
  if (ndigits == 1)
    return val1 * 16 + val1;
  else {
    int val2 = xvalue(s[1]);
    if (val2 < 0) return -1;
    return val1 * 16 + val2;
  }
}
