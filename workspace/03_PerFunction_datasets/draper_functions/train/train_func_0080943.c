ekg_resolver2(plugin_t *plugin, const char *server, watcher_handler_func_t async, void *data) {
	int res, fd[2];
	char *myserver;

	if (!server) {
		errno = EFAULT;
		return NULL;
	}

	debug("ekg_resolver2() resolving: %s\n", server);

	if (pipe(fd) == -1)
		return NULL;

	debug("ekg_resolver2() resolver pipes = { %d, %d }\n", fd[0], fd[1]);

	myserver = xstrdup(server);
	if ((res = fork()) == -1) {
		int errno2 = errno;

		close(fd[0]);
		close(fd[1]);
		xfree(myserver);
		errno = errno2;
		return NULL;
	}

	if (!res) {

		struct in_addr a;

		close(fd[0]);

#ifdef LIBIDN
		{
			char *tmp;

			if ((xstrspn(myserver, valid_hostname_chars_u) != xstrlen(myserver)) &&
				(idna_to_ascii_8z(myserver, &tmp, 0) == IDNA_SUCCESS)) {
				xfree(myserver);
				myserver = tmp;
			}
		}
#endif
		if ((a.s_addr = inet_addr(myserver)) == INADDR_NONE) {
			struct hostent *he = gethostbyname(myserver);

			if (!he)
				a.s_addr = INADDR_NONE;
			else
				memcpy(&a, he->h_addr_list[0], sizeof(a));
		}
		write(fd[1], &a, sizeof(a));
		xfree(myserver);
		sleep(1);
		exit(0);
	}


	close(fd[1]);
	xfree(myserver);

	return watch_add(plugin, fd[0], WATCH_READ, async, data);
}
