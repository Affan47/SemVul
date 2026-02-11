ct_cstring(void *p, size_t *len)
{
  dTHX;
  STRLEN l;
  const char *s = SvPV((SV*)p, l);
  if (len)
    *len = (size_t) l;
  return s;
}
