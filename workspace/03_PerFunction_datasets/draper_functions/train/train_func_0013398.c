xdrmem_control(XDR *xdrs, int request, void *info)
{
	xdr_bytesrec *xptr;

	switch (request) {
	case XDR_GET_BYTES_AVAIL:
		xptr = (xdr_bytesrec *) info;
		xptr->xc_is_last_record = TRUE;
		xptr->xc_num_avail = xdrs->x_handy;
		return (TRUE);
	default:
		return (FALSE);

	}

}
