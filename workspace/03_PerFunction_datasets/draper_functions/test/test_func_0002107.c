sock_connect_with_timeout(gint sock,
				      const struct sockaddr *serv_addr,
				      gint addrlen,
				      guint timeout_secs)
{
	gint ret;
#ifdef G_OS_UNIX
	void (*prev_handler)(gint);

	alarm(0);
	prev_handler = signal(SIGALRM, timeout_handler);
	if (sigsetjmp(jmpenv, 1)) {
		alarm(0);
		signal(SIGALRM, prev_handler);
		errno = ETIMEDOUT;
		log_error(LOG_PROTOCOL, _("Connection timed out.\n"));
		return -1;
	}
	alarm(timeout_secs);
#endif

	ret = connect(sock, serv_addr, addrlen);

#ifdef G_OS_UNIX
	alarm(0);
	signal(SIGALRM, prev_handler);
#endif

	return ret;
}
