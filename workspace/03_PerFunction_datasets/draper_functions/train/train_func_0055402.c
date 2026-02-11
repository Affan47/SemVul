xdrstdio_putlong(xdrs, lp)
XDR *xdrs;
const long *lp;
{

#ifndef mc68000
	long mycopy = htonl(*lp);

	lp = &mycopy;
#endif
	if (fwrite((char*) lp, sizeof(long), 1, (FILE *) xdrs->x_private) !=
		1) return (FALSE);

	return (TRUE);
}
