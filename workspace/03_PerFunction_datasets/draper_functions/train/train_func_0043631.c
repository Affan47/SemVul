conn_udpcon_init() {
	int fd, r;
	struct sockaddr_in6 baddr;
	fd = socket(AF_INET6, SOCK_DGRAM, 0);
	if(fd == -1) {
		logmsg(LOGGER_WARNING, "socket(): %s", strerror(errno));
		return -1;
	}
	fcntl(fd, F_SETFL, O_NONBLOCK);
	memset(&baddr, 0, sizeof(baddr));
	baddr.sin6_family = AF_INET6;
	baddr.sin6_port = htons(global_config.port);
	baddr.sin6_addr = in6addr_any;
	baddr.sin6_scope_id = 0;
	r = bind(fd, (struct sockaddr *)&baddr, sizeof(baddr));
	if(r == -1) {
		close(fd);
		logmsg(LOGGER_WARNING, "bind(): %s", strerror(errno));
		return -1;
	}
	conn_udpcon.fd = fd;
	conn_udpcon.sendbuf = NULL;
	conn_udpcon.sendbuflen = 0;
	conn_udpcon.recvbuf = NULL;
	conn_udpcon.recvbuflen = 0;
	conn_udpcon.recvbufsize = 0;
	return 0;
}
