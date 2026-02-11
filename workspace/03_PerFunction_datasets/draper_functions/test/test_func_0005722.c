xdr_dis_modulation_type(xdrs, objp)
	XDR *xdrs;
	dis_modulation_type *objp;
{
	if (!xdr_byte_u_short(xdrs, &objp->spread_spectrum)) {
		return (FALSE);
	}
	if (!xdr_byte_u_short(xdrs, &objp->major_type)) {
		return (FALSE);
	}
	if (!xdr_byte_u_short(xdrs, &objp->detail)) {
		return (FALSE);
	}
	if (!xdr_byte_u_short(xdrs, &objp->system)) {
		return (FALSE);
	}
	return (TRUE);
}
