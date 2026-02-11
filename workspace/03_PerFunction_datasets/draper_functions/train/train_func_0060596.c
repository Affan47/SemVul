unicodeisalpha(unsigned short c)
{
#ifdef OPENOFFICEORG
  return u_isalpha(c);
#else
  return (utf_tbl) ? utf_tbl[c].cletter : 0;
#endif
}
