tolower (int c)
{
  return c >= -128 && c < 256 ? __ctype_tolower[c] : c;
}
