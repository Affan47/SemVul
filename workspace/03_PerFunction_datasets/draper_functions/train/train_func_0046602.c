socket_read(int *id, int fd, short events, void *cbdata)
{
	struct sockaddr_in sin;
	int res;
	struct dundi_hdr *h;
	char buf[MAX_PACKET_SIZE];
	socklen_t len = sizeof(sin);

	res = recvfrom(netsocket, buf, sizeof(buf) - 1, 0,(struct sockaddr *) &sin, &len);
	if (res < 0) {
		if (errno != ECONNREFUSED)
			ast_log(LOG_WARNING, "Error: %s\n", strerror(errno));
		return 1;
	}
	if (res < sizeof(struct dundi_hdr)) {
		ast_log(LOG_WARNING, "midget packet received (%d of %d min)\n", res, (int)sizeof(struct dundi_hdr));
		return 1;
	}
	buf[res] = '\0';
	h = (struct dundi_hdr *) buf;
	if (dundidebug)
		dundi_showframe(h, 1, &sin, res - sizeof(struct dundi_hdr));
	AST_LIST_LOCK(&peers);
	handle_frame(h, &sin, res - sizeof(struct dundi_hdr));
	AST_LIST_UNLOCK(&peers);
	return 1;
}
