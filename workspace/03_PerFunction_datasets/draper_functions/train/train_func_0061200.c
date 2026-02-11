xdr_ndmp9_device_capability (XDR *xdrs, ndmp9_device_capability *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->device, ~0))
		 return FALSE;
	 if (!xdr_ndmp9_valid_u_long (xdrs, &objp->v3attr))
		 return FALSE;
	 if (!xdr_ndmp9_valid_u_long (xdrs, &objp->v4attr))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->capability.capability_val, (u_int *) &objp->capability.capability_len, ~0,
		sizeof (ndmp9_pval), (xdrproc_t) xdr_ndmp9_pval))
		 return FALSE;
	return TRUE;
}
