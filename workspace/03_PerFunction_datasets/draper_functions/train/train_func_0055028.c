open_vrrp_send_socket(sa_family_t family, int proto, int idx, int unicast)
{
	interface_t *ifp;
	int fd = -1;


	ifp = if_get_by_ifindex(idx);


	fd = socket(family, SOCK_RAW, proto);
	if (fd < 0) {
		log_message(LOG_INFO, "cant open raw socket. errno=%d", errno);
		return -1;
	}

	if (family == AF_INET) {

		if_setsockopt_hdrincl(&fd);
		if_setsockopt_bindtodevice(&fd, ifp);
		if (!unicast)
			if_setsockopt_mcast_loop(family, &fd);
		if_setsockopt_priority(&fd);
		if (fd < 0)
			return -1;
	} else if (family == AF_INET6) {

		if (!unicast) {
			if_setsockopt_mcast_hops(family, &fd);
			if_setsockopt_mcast_if(family, &fd, ifp);
			if_setsockopt_mcast_loop(family, &fd);
		}
		if_setsockopt_priority(&fd);
		if (fd < 0)
			return -1;
	} else {
		log_message(LOG_INFO, "cant open raw socket. unknow family=%d"
				    , family);
		close(fd);
		return -1;
	}

	return fd;
}
