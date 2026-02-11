socket_transport_recv (void *buf, int len)
{
	int res;
	int total = 0;
	int fd = conn_fd;
	int flags = 0;
	static gint32 last_keepalive;
	gint32 msecs;

	do {
	again:
		res = recv (fd, (char *) buf + total, len - total, flags);
		if (res > 0)
			total += res;
		if (agent_config.keepalive) {
			gboolean need_keepalive = FALSE;
			if (res == -1 && get_last_sock_error () == MONO_EWOULDBLOCK) {
				need_keepalive = TRUE;
			} else if (res == -1) {

				msecs = mono_msec_ticks ();
				if (msecs - last_keepalive >= agent_config.keepalive) {
					need_keepalive = TRUE;
					last_keepalive = msecs;
				}
			}
			if (need_keepalive) {
				process_profiler_event (EVENT_KIND_KEEPALIVE, NULL);
				goto again;
			}
		}
	} while ((res > 0 && total < len) || (res == -1 && get_last_sock_error () == MONO_EINTR));
	return total;
}
