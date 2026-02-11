isns_connect(void)
{
	int fd, err;

	fd = socket(ss.ss_family, SOCK_STREAM, IPPROTO_TCP);
	if (fd < 0) {
		log_error("unable to create (%s) %d!", strerror(errno),
			  ss.ss_family);
		return -1;
	}

	err = connect(fd, (struct sockaddr *) &ss, sizeof(ss));
	if (err < 0) {
		log_error("unable to connect (%s) %d!", strerror(errno),
			  ss.ss_family);
		close(fd);
		return -1;
	}

	log_error("%s %d: new connection %d", __FUNCTION__, __LINE__, fd);

	if (!strlen(eid)) {
		err = isns_get_ip(fd);
		if (err) {
			close(fd);
			return -1;
		}
	}

	isns_fd = fd;
	isns_set_fd(fd, scn_listen_fd, scn_fd);

	return fd;
}
