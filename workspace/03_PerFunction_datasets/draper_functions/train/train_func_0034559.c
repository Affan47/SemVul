io_conn_ind(void)
{
	struct vhci_link_info info;
	struct vhci_conn *conn;
	struct sockaddr_in sa;
	socklen_t len;
	int nsk, h;

	len = sizeof(sa);
	if ((nsk = accept(vdev.scan_fd, (struct sockaddr *) &sa, &len)) < 0)
		return;

	if (read_n(nsk, &info, sizeof(info)) < 0) {
		syslog(LOG_ERR, "Can't read link info");
		return;
	}

	if (!(conn = malloc(sizeof(*conn)))) {
		syslog(LOG_ERR, "Can't alloc new connection");
		close(nsk);
		return;
	}

	bacpy(&conn->dest, &info.bdaddr);

	for (h = 0; h < VHCI_MAX_CONN; h++)
		if (!vconn[h])
			goto accepted;

	syslog(LOG_ERR, "Too many connections");
	free(conn);
	close(nsk);
	return;

accepted:
	vconn[h] = conn;
	conn->handle = h + 1;
	conn->fd = nsk;
	connect_request(conn);
}
