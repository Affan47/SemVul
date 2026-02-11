gfm_client_rpc_request(struct gfm_connection *gfm_server, int command,
		       const char *format, ...)
{
	va_list ap;
	gfarm_error_t e;

	va_start(ap, format);
	e = gfp_xdr_vrpc_request(gfm_server->conn, command, &format, &ap);
	va_end(ap);
	if (IS_CONNECTION_ERROR(e))
		gfm_client_purge_from_cache(gfm_server);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1001104,
			"gfp_xdr_vrpc_request(%d) failed: %s",
			command,
			gfarm_error_string(e));
	}
	return (e);
}
