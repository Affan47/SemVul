xdr_dis_articulation_parm(XDR * xdrs, dis_articulation_parm * objp)
{
	if (!xdr_byte_u_char(xdrs, &objp->type)) {
		return (FALSE);
	}
	if (!xdr_byte_u_char(xdrs, &objp->change)) {
		return (FALSE);
	}
	if (!xdr_byte_short(xdrs, &objp->id)) {
		return (FALSE);
	}
	if (!xdr_byte_long(xdrs, (char *) &objp->type)) {
		return (FALSE);
	}
	switch (objp->type) {
	default:
		objp->value.l[0] = 0;
		objp->value.l[1] = 0;
	}
	return TRUE;
}
