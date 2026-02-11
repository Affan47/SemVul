calltab_entry(ax25_address *callsign,int *flags)
{
  struct callsign_list *c;
  int flagdummy;

  if (flags == NULL)
    flags = &flagdummy;
  *flags = 0;
  for (c = calltab; c; c = c->next) {
    if ((c->flags&C_IS_FLOOD
	 && (*flags = floodcmp(c->callsign,c->floodlen,callsign)))
	|| (ax25_cmp(c->callsign,callsign) == 0)) {
      *flags |= c->flags;
      return c;
    }
  }
  return NULL;
}
