dessert_cli_run() {
	_dessert_cli_running = 1;
	int on = 1;


	_dessert_cli_sock = socket(AF_INET6, SOCK_STREAM, 0);
	setsockopt(_dessert_cli_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	memset(&_dessert_cli_addr, 0, sizeof(_dessert_cli_addr));
	_dessert_cli_addr.sin6_family = AF_INET6;
	_dessert_cli_addr.sin6_addr = in6addr_any;
	_dessert_cli_addr.sin6_port = htons(_cli_port);
	if (bind(_dessert_cli_sock, (struct sockaddr *) &_dessert_cli_addr,
			sizeof(_dessert_cli_addr))) {
		dessert_err("cli socket bind to port %d failed - %s", _cli_port, strerror(errno));
		return -errno;
	}
	listen(_dessert_cli_sock, 8);
	dessert_debug("starting worker thread for cli");
	pthread_create(&_dessert_cli_worker, NULL, _dessert_cli_accept_thread,
			&_dessert_cli_sock);
	return DESSERT_OK;
}
