xdr_ndmp2_connect_client_auth_request (XDR *xdrs, ndmp2_connect_client_auth_request *objp)
{
	register int32_t *buf;

	 if (!xdr_ndmp2_auth_data (xdrs, &objp->auth_data))
		 return FALSE;
	return TRUE;
}
