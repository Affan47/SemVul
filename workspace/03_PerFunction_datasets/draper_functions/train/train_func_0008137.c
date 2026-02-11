tcp_pause_listener(struct listener *l)
{
	if (shutdown(l->fd, SHUT_WR) != 0)
		return -1;

	if (listen(l->fd, l->backlog ? l->backlog : l->maxconn) != 0)
		return -1;

	if (shutdown(l->fd, SHUT_RD) != 0)
		return -1;
	return 1;
}
