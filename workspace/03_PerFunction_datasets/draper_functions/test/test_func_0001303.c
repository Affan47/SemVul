handle_connection(int n)
{
    int status = 0;
    int connfd;
    int listenfd = srvtab[n].fd;

    server_addr = *srvtab[n].addr;
    server_addrlen = srvtab[n].addrlen;

    client_addrlen = sizeof(client_addr);
    connfd = accept(listenfd, &client_addr, &client_addrlen);

    if (connfd == -1) {
	if (errno == EINTR)
	    return -1;
	dico_log(L_ERR, errno, "accept");
	return -1;

    }

    if (dicod_acl_check(connect_acl, 1) == 0) {
	char *p = sockaddr_to_astr(&client_addr, client_addrlen);
	dico_log(L_NOTICE, 0,
		 _("connection from %s denied"),
		 p);
	free(p);
	SWRITE(connfd, ACCESS_DENIED_MSG);
	close(connfd);
	return 0;
    }

    if (single_process) {
	int status;
	dico_stream_t str = dicod_iostream(connfd, connfd);
	if (str) {
	    status = dicod_loop(str);
	    dico_stream_close(str);
	    dico_stream_destroy(&str);
	}
    } else {
	pid_t pid = fork();
	if (pid == -1) {
	    dico_log(L_ERR, errno, "fork");
	    SWRITE(connfd, TEMP_FAIL_MSG);
	} else if (pid == 0) {

	    dico_stream_t str;

	    close(listenfd);

	    signal(SIGTERM, SIG_DFL);
	    signal(SIGQUIT, SIG_DFL);
	    signal(SIGINT, SIG_DFL);
	    signal(SIGCHLD, SIG_DFL);
	    signal(SIGHUP, SIG_DFL);

	    str = dicod_iostream(connfd, connfd);
	    if (!str)
		exit(EX_UNAVAILABLE);
	    status = dicod_loop(str);
	    dico_stream_close(str);
	    dico_stream_destroy(&str);
	    exit(status);
	} else {
	    register_child(pid);
	}
    }
    close(connfd);
    return status;
}
