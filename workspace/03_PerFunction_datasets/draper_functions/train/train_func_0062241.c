xdr_ndmp3_file (XDR *xdrs, ndmp3_file *objp)
{
	register int32_t *buf;

	 if (!xdr_array (xdrs, (char **)&objp->names.names_val, (u_int *) &objp->names.names_len, ~0,
		sizeof (ndmp3_file_name), (xdrproc_t) xdr_ndmp3_file_name))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->stats.stats_val, (u_int *) &objp->stats.stats_len, ~0,
		sizeof (ndmp3_file_stat), (xdrproc_t) xdr_ndmp3_file_stat))
		 return FALSE;
	 if (!xdr_ndmp3_u_quad (xdrs, &objp->node))
		 return FALSE;
	 if (!xdr_ndmp3_u_quad (xdrs, &objp->fh_info))
		 return FALSE;
	return TRUE;
}
