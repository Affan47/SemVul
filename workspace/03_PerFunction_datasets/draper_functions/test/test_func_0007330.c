accept_connection(int afd, int events, void *data)
{
	struct sockaddr_storage from;
	socklen_t namesize;
	struct iscsi_connection *conn;
	struct iscsi_tcp_connection *tcp_conn;
	int fd, ret;

	dprintf("%d\n", afd);

	namesize = sizeof(from);
	fd = accept(afd, (struct sockaddr *) &from, &namesize);
	if (fd < 0) {
		eprintf("can't accept, %m\n");
		return;
	}

	if (!is_system_available())
		goto out;

	if (list_empty(&iscsi_targets_list))
		goto out;

	ret = set_keepalive(fd);
	if (ret)
		goto out;

	ret = set_nodelay(fd);
	if (ret)
		goto out;

	tcp_conn = zalloc(sizeof(*tcp_conn));
	if (!tcp_conn)
		goto out;

	conn = &tcp_conn->iscsi_conn;

	ret = conn_init(conn);
	if (ret) {
		free(tcp_conn);
		goto out;
	}

	tcp_conn->fd = fd;
	conn->tp = &iscsi_tcp;

	conn_read_pdu(conn);
	set_non_blocking(fd);

	ret = tgt_event_add(fd, EPOLLIN, iscsi_tcp_event_handler, conn);
	if (ret) {
		conn_exit(conn);
		free(tcp_conn);
		goto out;
	}

	return;
out:
	close(fd);
	return;
}
