xdr_ndmp9_data_get_state_reply (XDR *xdrs, ndmp9_data_get_state_reply *objp)
{
	register int32_t *buf;

	 if (!xdr_ndmp9_error (xdrs, &objp->error))
		 return FALSE;
	 if (!xdr_ndmp9_data_operation (xdrs, &objp->operation))
		 return FALSE;
	 if (!xdr_ndmp9_data_state (xdrs, &objp->state))
		 return FALSE;
	 if (!xdr_ndmp9_data_halt_reason (xdrs, &objp->halt_reason))
		 return FALSE;
	 if (!xdr_ndmp9_u_quad (xdrs, &objp->bytes_processed))
		 return FALSE;
	 if (!xdr_ndmp9_valid_u_quad (xdrs, &objp->est_bytes_remain))
		 return FALSE;
	 if (!xdr_ndmp9_valid_u_long (xdrs, &objp->est_time_remain))
		 return FALSE;
	 if (!xdr_ndmp9_addr (xdrs, &objp->data_connection_addr))
		 return FALSE;
	 if (!xdr_ndmp9_u_quad (xdrs, &objp->read_offset))
		 return FALSE;
	 if (!xdr_ndmp9_u_quad (xdrs, &objp->read_length))
		 return FALSE;
	return TRUE;
}
