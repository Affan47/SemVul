xdr_gfs3_link_req (XDR *xdrs, gfs3_link_req *objp)
{
	register int32_t *buf;
        buf = NULL;

	 if (!xdr_opaque (xdrs, objp->oldgfid, 16))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->newgfid, 16))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->newbname, ~0))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->xdata.xdata_val, (u_int *) &objp->xdata.xdata_len, ~0))
		 return FALSE;
	return TRUE;
}
