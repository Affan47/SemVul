scn_accept_connection(int dummy, int events, void *data)
{
	struct sockaddr_storage from;
	socklen_t slen;
	int fd, err, opt = 1;

	slen = sizeof(from);
	fd = accept(scn_listen_fd, (struct sockaddr *) &from, &slen);
	if (fd < 0) {
		eprintf("accept error %m\n");
		return;
	}
	eprintf("Accept scn connection %d\n", fd);

	err = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
	if (err)
		eprintf("%m\n");


	scn_fd = fd;
	tgt_event_add(scn_fd, EPOLLIN, isns_scn_handle, NULL);

	return;
}
