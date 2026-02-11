gfm_client_get_nhosts(struct gfm_connection *gfm_server,
	int nhosts, struct gfarm_host_info *hosts)
{
	gfarm_error_t e;
	int i, eof;
	gfarm_int32_t naliases;

	for (i = 0; i < nhosts; i++) {
		e = gfp_xdr_recv(gfm_server->conn, 0, &eof, "ssiiii",
		    &hosts[i].hostname, &hosts[i].architecture,
		    &hosts[i].ncpu, &hosts[i].port, &hosts[i].flags,
		    &naliases);
		if (IS_CONNECTION_ERROR(e))
			gfm_client_purge_from_cache(gfm_server);
		if (e != GFARM_ERR_NO_ERROR) {
			gflog_debug(GFARM_MSG_1001110,
				"gfp_xdr_recv() failed: %s",
				gfarm_error_string(e));
			return (e);
		}
		if (eof) {
			gflog_debug(GFARM_MSG_1001111,
				"Unexpected EOF when receiving response: %s",
				gfarm_error_string(GFARM_ERR_PROTOCOL));
			return (GFARM_ERR_PROTOCOL);
		}

		hosts[i].nhostaliases = 0;
		hosts[i].hostaliases = NULL;
	}
	return (GFARM_ERR_NO_ERROR);
}
