floodcmp(ax25_address *f, int len, ax25_address *c)
{
  int i;

  for (i = 0; i < len; i++)
    if ((f->ax25_call[i] & 0xFE) != (c->ax25_call[i] & 0xFE))
      return C_IS_NOFLOOD;
  return floodtype(c,i);
}
