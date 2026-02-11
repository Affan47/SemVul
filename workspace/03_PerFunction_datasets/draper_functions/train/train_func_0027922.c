xdr_gd1_mgmt_unfriend_rsp (XDR *xdrs, gd1_mgmt_unfriend_rsp *objp)
{
	register int32_t *buf;
        buf = NULL;

	 if (!xdr_vector (xdrs, (char *)objp->uuid, 16,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->hostname, ~0))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->op_ret))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->op_errno))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->port))
		 return FALSE;
	return TRUE;
}
