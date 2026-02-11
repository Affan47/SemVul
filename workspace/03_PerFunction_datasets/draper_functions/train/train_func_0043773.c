xdr_ndmp9_execute_cdb_reply (XDR *xdrs, ndmp9_execute_cdb_reply *objp)
{
	register int32_t *buf;

	 if (!xdr_ndmp9_error (xdrs, &objp->error))
		 return FALSE;
	 if (!xdr_u_char (xdrs, &objp->status))
		 return FALSE;
	 if (!xdr_u_long (xdrs, &objp->dataout_len))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->datain.datain_val, (u_int *) &objp->datain.datain_len, ~0))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->ext_sense.ext_sense_val, (u_int *) &objp->ext_sense.ext_sense_len, ~0))
		 return FALSE;
	return TRUE;
}
