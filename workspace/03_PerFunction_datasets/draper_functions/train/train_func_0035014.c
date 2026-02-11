ipmi_lan_recv_packet(struct ipmi_intf * intf)
{
	static struct ipmi_rs rsp;
	fd_set read_set, err_set;
	struct timeval tmout;
	int ret;

	FD_ZERO(&read_set);
	FD_SET(intf->fd, &read_set);

	FD_ZERO(&err_set);
	FD_SET(intf->fd, &err_set);

	tmout.tv_sec = intf->session->timeout;
	tmout.tv_usec = 0;

	ret = select(intf->fd + 1, &read_set, NULL, &err_set, &tmout);
	if (ret < 0 || FD_ISSET(intf->fd, &err_set) || !FD_ISSET(intf->fd, &read_set))
		return NULL;

	memset(&rsp, 0, sizeof(rsp));


	ret = recv(intf->fd, &rsp.data, IPMI_BUF_SIZE, 0);

	if (ret < 0) {
		FD_ZERO(&read_set);
		FD_SET(intf->fd, &read_set);

		FD_ZERO(&err_set);
		FD_SET(intf->fd, &err_set);

		tmout.tv_sec = intf->session->timeout;
		tmout.tv_usec = 0;

		ret = select(intf->fd + 1, &read_set, NULL, &err_set, &tmout);
		if (ret < 0 || FD_ISSET(intf->fd, &err_set) || !FD_ISSET(intf->fd, &read_set))
			return NULL;

		ret = recv(intf->fd, &rsp.data, IPMI_BUF_SIZE, 0);
		if (ret < 0)
			return NULL;
	}

	if (ret == 0)
		return NULL;

	rsp.data[ret] = '\0';
	rsp.data_len = ret;

	if (verbose > 2)
		printbuf(rsp.data, rsp.data_len, "recv_packet");

	return &rsp;
}
