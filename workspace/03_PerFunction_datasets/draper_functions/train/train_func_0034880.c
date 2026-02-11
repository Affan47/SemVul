authgss_marshal(AUTH *auth, XDR *xdrs)
{
	XDR			 tmpxdrs;
	char			 tmp[MAX_AUTH_BYTES];
	struct rpc_gss_data	*gd;
	gss_buffer_desc		 rpcbuf, checksum;
	OM_uint32		 maj_stat, min_stat;
	bool_t			 xdr_stat;

	log_debug("in authgss_marshal()");

	gd = AUTH_PRIVATE(auth);

	if (gd->established)
		gd->gc.gc_seq++;

	xdrmem_create(&tmpxdrs, tmp, sizeof(tmp), XDR_ENCODE);

	if (!xdr_rpc_gss_cred(&tmpxdrs, &gd->gc)) {
		XDR_DESTROY(&tmpxdrs);
		return (FALSE);
	}
	auth->ah_cred.oa_flavor = RPCSEC_GSS;
	auth->ah_cred.oa_base = tmp;
	auth->ah_cred.oa_length = XDR_GETPOS(&tmpxdrs);

	XDR_DESTROY(&tmpxdrs);

	if (!xdr_opaque_auth(xdrs, &auth->ah_cred))
		return (FALSE);

	if (gd->gc.gc_proc == RPCSEC_GSS_INIT ||
	    gd->gc.gc_proc == RPCSEC_GSS_CONTINUE_INIT) {
		return (xdr_opaque_auth(xdrs, &gssrpc__null_auth));
	}

	rpcbuf.length = XDR_GETPOS(xdrs);
	XDR_SETPOS(xdrs, 0);
	rpcbuf.value = XDR_INLINE(xdrs, (int)rpcbuf.length);

	maj_stat = gss_get_mic(&min_stat, gd->ctx, gd->sec.qop,
			    &rpcbuf, &checksum);

	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_get_mic", maj_stat, min_stat);
		if (maj_stat == GSS_S_CONTEXT_EXPIRED) {
			gd->established = FALSE;
			authgss_destroy_context(auth);
		}
		return (FALSE);
	}
	auth->ah_verf.oa_flavor = RPCSEC_GSS;
	auth->ah_verf.oa_base = checksum.value;
	auth->ah_verf.oa_length = checksum.length;

	xdr_stat = xdr_opaque_auth(xdrs, &auth->ah_verf);
	gss_release_buffer(&min_stat, &checksum);

	return (xdr_stat);
}
