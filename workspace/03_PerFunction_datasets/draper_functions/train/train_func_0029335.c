host_info_get_by_name_alias(struct gfm_connection *gfm_server,
	const char *hostname, struct gfarm_host_info *info)
{
	gfarm_error_t e, e2;

	e = gfm_client_host_info_get_by_namealiases(gfm_server,
	    1, &hostname, &e2, info);
	if (e != GFARM_ERR_NO_ERROR || e2 != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1000866,
			"gfm_client_host_info_get_by_namealiases(%s) failed: "
			"%s",
			hostname,
			gfarm_error_string(e != GFARM_ERR_NO_ERROR ? e : e2));
	}
	return (e != GFARM_ERR_NO_ERROR ? e : e2);
}
