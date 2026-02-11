xdrmem_putbytes(XDR *xdrs, caddr_t addr, int len)
{
	if ((uint32_t)len > (uint32_t)xdrs->x_handy) {
		xdrs->x_private += (u_int)xdrs->x_handy;
		xdrs->x_handy = 0;
		return (FALSE);
	}
	xdrs->x_handy -= len;
	(void) memcpy(xdrs->x_private, addr, (u_int)len);
	xdrs->x_private += (u_int)len;
	return (TRUE);
}
