xdr_mountres3_ok (XDR *xdrs, mountres3_ok *objp)
{
	 if (!xdr_fhandle3 (xdrs, &objp->fhandle))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->auth_flavors.auth_flavors_val, (u_int *) &objp->auth_flavors.auth_flavors_len, ~0,
		sizeof (int), (xdrproc_t) xdr_int))
		 return FALSE;
	return TRUE;
}
