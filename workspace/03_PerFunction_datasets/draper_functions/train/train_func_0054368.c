gfp_xdr_vrecv_request_parameters(struct gfp_xdr *client, int just,
	size_t *sizep, const char *format, va_list *app)
{
	gfarm_error_t e;
	int eof;

	e = gfp_xdr_vrecv_sized(client, just, sizep, &eof, &format, app);
	if (e != GFARM_ERR_NO_ERROR)
		return (e);
	if (eof)
		return (GFARM_ERR_UNEXPECTED_EOF);
	if (*format != '\0') {
		gflog_debug(GFARM_MSG_1001017,
		    "gfp_xdr_vrecv_request_parameters: "
		    "invalid format character: %c(%x)", *format, *format);
		return (GFARM_ERRMSG_GFP_XDR_VRPC_INVALID_FORMAT_CHARACTER);
	}
	if (sizep != NULL && *sizep != 0) {
		gflog_debug(GFARM_MSG_1001018,
		    "gfp_xdr_vrecv_request_parameters: residual %d bytes",
		    (int)*sizep);
		return (GFARM_ERR_PROTOCOL);
	}
	return (GFARM_ERR_NO_ERROR);
}
