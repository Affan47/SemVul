xdrmem_setpos(xdrs, pos)
register XDR *xdrs;
unsigned int pos;
{
  register char* newaddr = xdrs->x_base + pos;
  register char* lastaddr = xdrs->x_private + xdrs->x_handy;

  if ((long) newaddr > (long) lastaddr
	  || (UINT_MAX < LONG_MAX
		  && (long) UINT_MAX < (long) lastaddr - (long) newaddr))
	  return (FALSE);
  xdrs->x_private = newaddr;
  xdrs->x_handy = (long) lastaddr - (long) newaddr;
  return (TRUE);
}
