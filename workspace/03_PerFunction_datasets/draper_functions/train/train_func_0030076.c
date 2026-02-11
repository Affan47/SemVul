autodetect()
{
	struct pollfd pfd[1];
	int ns;
	int rc;

	ns = rtnl_socket();
	if (ns < 0)
		return ns;

	send_getlink_dump(ns);
	pfd[0].fd = ns;
	pfd[0].events = POLLIN;

	while (1) {
		rc = poll(pfd, ARRAY_SIZE(pfd), TIMEOUT);
		log_debug(1, "return from poll %d", rc);
		if (rc == 0)
			break;
		if (rc == -1) {
			log_errno("poll error");
			break;
		}
		if (pfd[0].revents) {
			rc = rtnl_recv(pfd[0].fd);
			if (rc == 0)
				break;
		}
		pfd[0].revents = 0;
	}
	close(ns);
	return 0;
}
