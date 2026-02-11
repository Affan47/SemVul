xdrmem_putint32_unaligned(XDR *xdrs, int32_t *ip)
{
    int32_t i;

	if (sizeof (int32_t) > (uint32_t)xdrs->x_handy) {
		xdrs->x_private += (u_int)xdrs->x_handy;
		xdrs->x_handy = 0;
		return (FALSE);
	}
	xdrs->x_handy -= sizeof (int32_t);
	i = (int32_t)xdr_hton32((uint32_t)(*ip));
	memcpy(xdrs->x_private, &i, sizeof(int32_t));
	xdrs->x_private += sizeof (int32_t);
	return (TRUE);
}
