xdr_gfs3_fentrylk_req (XDR *xdrs, gfs3_fentrylk_req *objp)
{
	register int32_t *buf;
        buf = NULL;

	 if (!xdr_opaque (xdrs, objp->gfid, 16))
		 return FALSE;
	 if (!xdr_quad_t (xdrs, &objp->fd))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->cmd))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->type))
		 return FALSE;
	 if (!xdr_u_quad_t (xdrs, &objp->namelen))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->name, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->volume, ~0))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->xdata.xdata_val, (u_int *) &objp->xdata.xdata_len, ~0))
		 return FALSE;
	return TRUE;
}
