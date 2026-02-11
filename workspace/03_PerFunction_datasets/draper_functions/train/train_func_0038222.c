xdr_dis_beam_antenna_pattern(xdrs, objp)
	XDR *xdrs;
	dis_beam_antenna_pattern *objp;
{
	if (!xdr_dis_euler_angles(xdrs, &objp->direction)) {
		return (FALSE);
	}
	if (!xdr_byte_float(xdrs, &objp->azimuth_width)) {
		return (FALSE);
	}
	if (!xdr_byte_float(xdrs, &objp->elev_width)) {
		return (FALSE);
	}
	if (!xdr_byte_u_char(xdrs, &objp->reference_system)) {
		return (FALSE);
	}
	if (!xdr_vector(xdrs, (char *)objp->pad, 3, sizeof(byte_u_char), xdr_byte_u_char)) {
		return (FALSE);
	}
	if (!xdr_byte_float(xdrs, &objp->Ez)) {
		return (FALSE);
	}
	if (!xdr_byte_float(xdrs, &objp->Ex)) {
		return (FALSE);
	}
	if (!xdr_byte_float(xdrs, &objp->phase)) {
		return (FALSE);
	}
	return (TRUE);
}
