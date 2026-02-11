my_charpos_utf16(CHARSET_INFO *cs,
                 const char *b, const char *e, size_t pos)
{
  const char *b0= b;
  uint charlen;

  for ( ; pos; b+= charlen, pos--)
  {
    if (!(charlen= my_ismbchar(cs, b, e)))
      return (e + 2 - b0);
  }
  return (size_t) (pos ? (e + 2 - b0) : (b - b0));
}
