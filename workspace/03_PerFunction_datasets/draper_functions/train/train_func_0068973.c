gfm_client_host_info_get_n(struct gfm_connection *gfm_server, int nhosts,
	int *nhostsp, struct gfarm_host_info **hostsp, const char *diag)
{
	gfarm_error_t e;
	struct gfarm_host_info *hosts;

	GFARM_MALLOC_ARRAY(hosts, nhosts);
	if (hosts == NULL) {
		gflog_debug(GFARM_MSG_1002208,
		    "host_info allocation for %d hosts: no memory", nhosts);
		return (GFARM_ERR_NO_MEMORY);
	}
	if ((e = gfm_client_get_nhosts(gfm_server, nhosts, hosts))
	    != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1001114,
		    "gfm_client_get_nhosts() failed: %s",
		    gfarm_error_string(e));
		return (e);
	}
	*nhostsp = nhosts;
	*hostsp = hosts;
	return (GFARM_ERR_NO_ERROR);
}
