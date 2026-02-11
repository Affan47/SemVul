gfm_host_info_get_by_name_alias(struct gfm_connection *gfm_server,
	const char *if_hostname, struct gfarm_host_info *info)
{
	gfarm_error_t e;
	struct hostent *hp;
	int i;
	char *n;

	e = host_info_get_by_name_alias(gfm_server, if_hostname, info);
	if (e == GFARM_ERR_NO_ERROR)
		return (GFARM_ERR_NO_ERROR);


	hp = gethostbyname(if_hostname);
	if (hp == NULL || hp->h_addrtype != AF_INET) {
		gflog_debug(GFARM_MSG_1000867,
			"Unknown host (%s): %s",
			if_hostname,
			gfarm_error_string(GFARM_ERR_UNKNOWN_HOST));
		return (GFARM_ERR_UNKNOWN_HOST);
	}
	for (i = 0, n = hp->h_name; n != NULL; n = hp->h_aliases[i++]){
		if (host_info_get_by_name_alias(gfm_server, n, info) ==
		    GFARM_ERR_NO_ERROR)
			return (GFARM_ERR_NO_ERROR);
	}
	return (e);
}
