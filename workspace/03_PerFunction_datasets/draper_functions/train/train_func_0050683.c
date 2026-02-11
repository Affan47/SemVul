After_Last_Whitespace_Character(FIELD_CELL *buf, int blen)
{
  FIELD_CELL *p = &buf[blen];

  assert(buf && blen >= 0);
  while ((p > buf) && !ISBLANK(p[-1]))
    p--;
  return (p);
}
