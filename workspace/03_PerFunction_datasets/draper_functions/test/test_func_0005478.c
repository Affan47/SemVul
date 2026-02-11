xdr_gfs3_dirplist (XDR *xdrs, gfs3_dirplist *objp)
{
	register int32_t *buf;
        buf = NULL;

	 if (!xdr_u_quad_t (xdrs, &objp->d_ino))
		 return FALSE;
	 if (!xdr_u_quad_t (xdrs, &objp->d_off))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->d_len))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->d_type))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->name, ~0))
		 return FALSE;
	 if (!xdr_gf_iatt (xdrs, &objp->stat))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->dict.dict_val, (u_int *) &objp->dict.dict_len, ~0))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->nextentry, sizeof (gfs3_dirplist), (xdrproc_t) xdr_gfs3_dirplist))
		 return FALSE;
	return TRUE;
}
