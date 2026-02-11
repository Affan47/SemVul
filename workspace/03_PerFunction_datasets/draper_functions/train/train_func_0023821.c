start_client_info_sock(char *host_port_cookie) {
	char *host = NULL, *cookie = NULL, *p;
	char *str = strdup(host_port_cookie);
	int i, port, sock, next = -1;
	static time_t start_time[ICON_MODE_SOCKS];
	time_t oldest = 0;
	int db = 0;

	port = -1;

	for (i = 0; i < ICON_MODE_SOCKS; i++) {
		if (icon_mode_socks[i] < 0) {
			next = i;
			break;
		}
		if (oldest == 0 || start_time[i] < oldest) {
			next = i;
			oldest = start_time[i];
		}
	}

	p = strtok(str, ":");
	i = 0;
	while (p) {
		if (i == 0) {
			host = strdup(p);
		} else if (i == 1) {
			port = atoi(p);
		} else if (i == 2) {
			cookie = strdup(p);
		}
		i++;
		p = strtok(NULL, ":");
	}
	free(str);

	if (db) fprintf(stderr, "%s/%d/%s next=%d\n", host, port, cookie, next);

	if (host && port && cookie) {
		if (*host == '\0') {
			free(host);
			host = strdup("localhost");
		}
		sock = connect_tcp(host, port);
		if (sock < 0) {
			usleep(200 * 1000);
			sock = connect_tcp(host, port);
		}
		if (sock >= 0) {
			char *lst = list_clients();
			icon_mode_socks[next] = sock;
			start_time[next] = time(NULL);
			write(sock, "COOKIE:", strlen("COOKIE:"));
			write(sock, cookie, strlen(cookie));
			write(sock, "\n", strlen("\n"));
			write(sock, "none\n", strlen("none\n"));
			write(sock, "none\n", strlen("none\n"));
			write(sock, lst, strlen(lst));
			write(sock, "\n", strlen("\n"));
			if (db) {
				fprintf(stderr, "list: %s\n", lst);
			}
			free(lst);
			rfbLog("client_info_sock to: %s:%d\n", host, port);
		} else {
			rfbLog("failed client_info_sock: %s:%d\n", host, port);
		}
	} else {
		rfbLog("malformed client_info_sock: %s\n", host_port_cookie);
	}

	if (host) free(host);
	if (cookie) free(cookie);
}
