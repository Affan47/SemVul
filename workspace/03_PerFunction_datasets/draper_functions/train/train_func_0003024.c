processnewclient(void) {
	client_t *newclient = xalloc(sizeof *newclient);

	newclient->fd = accept(sockfd, NULL, NULL);

	if(newclient->fd < 0) {
		free(newclient);
		if(errno == ECONNABORTED || errno == EINTR)
			return;
		syslog(LOG_ERR, "Error during accept(): %s\n", strerror(errno));
		exit(EX_OSERR);
	}

        int flags = fcntl(newclient->fd, F_GETFL);
        fcntl(newclient->fd, F_SETFL, flags | O_NONBLOCK);

	newclient->next = clients;
	clients = newclient;
}
