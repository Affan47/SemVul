fmt_ullnumwa(char* buffer, unsigned long long u,
			     unsigned width, char pad,
			     unsigned base, const char* digits,
			     const char* prefix)
{
  unsigned prefixlen = 0;
  if (prefix != 0) {
    prefixlen = strlen(prefix);
    width = (width > prefixlen) ? width - prefixlen : 0;
    if (buffer != 0)
      for (; *prefix != 0; ++prefix, ++buffer)
	*buffer = *prefix;
  }
  return prefixlen + fmt_ullnumw(buffer, u, width, pad, base, digits);
}
