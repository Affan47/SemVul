run_rconnection(struct connection *cn)
{
	int n;
	short r;

	n = cn->pollno;
	if (n == -1)
		return;
	r = pollfds[n].revents;
	if (r & POLLERR || r == POLLHUP) {
		close_connection(cn);
		return;
	}
	if (r & POLLIN) {
		if (read_connection(cn) == -1 || scan_request(cn) == -1)
			return;
		r &= ~POLLIN;
		if (cn->connection_state == HC_WRITING)
			r |= POLLOUT;
		pollfds[n].revents = r;
	}
}
