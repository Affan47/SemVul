host_info_address_get_matched(struct gfarm_host_info *info, int port,
	struct gfarm_hostspec *hostspec,
	struct sockaddr *peer_addr, char **if_hostnamep)
{
	gfarm_error_t e;
	int i;

	e = host_address_get_matched(info->hostname, port, hostspec,
	    peer_addr, if_hostnamep);
	if (e == GFARM_ERR_NO_ERROR)
		return (GFARM_ERR_NO_ERROR);
	for (i = 0; i < info->nhostaliases; i++) {
		e = host_address_get_matched(info->hostaliases[i], port,
		    hostspec, peer_addr, if_hostnamep);
		if (e == GFARM_ERR_NO_ERROR)
			return (GFARM_ERR_NO_ERROR);
	}
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1000882,
		"failed to get matched host address: %s",
		gfarm_error_string(e));
	}
	return (e);
}
