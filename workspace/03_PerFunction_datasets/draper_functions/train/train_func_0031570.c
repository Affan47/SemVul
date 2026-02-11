xdr_gfs3_symlink_rsp (XDR *xdrs, gfs3_symlink_rsp *objp)
{
	register int32_t *buf;
        buf = NULL;

	 if (!xdr_int (xdrs, &objp->op_ret))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->op_errno))
		 return FALSE;
	 if (!xdr_gf_iatt (xdrs, &objp->stat))
		 return FALSE;
	 if (!xdr_gf_iatt (xdrs, &objp->preparent))
		 return FALSE;
	 if (!xdr_gf_iatt (xdrs, &objp->postparent))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->xdata.xdata_val, (u_int *) &objp->xdata.xdata_len, ~0))
		 return FALSE;
	return TRUE;
}
