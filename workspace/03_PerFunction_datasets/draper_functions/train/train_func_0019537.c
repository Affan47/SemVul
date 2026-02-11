main(int argc, char *argv[])
{
	int fd;
	struct sockaddr_un sock_address;
	char msg[BUFSIZ], rsp[BUFSIZ];

	if (argc < 2)
		err("No arguments given.\n");

	sock_address.sun_family = AF_UNIX;
	char *sp;

	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		err("Failed to create the socket.\n");

	sp = getenv(SOCKET_ENV_VAR);
	if (sp != NULL) {
		snprintf(sock_address.sun_path, sizeof(sock_address.sun_path), "%s", sp);
	} else {
		char *host = NULL;
		int dn = 0, sn = 0;
		if (xcb_parse_display(NULL, &host, &dn, &sn) != 0)
			snprintf(sock_address.sun_path, sizeof(sock_address.sun_path), SOCKET_PATH_TPL, host, dn, sn);
		free(host);
	}

	if (connect(fd, (struct sockaddr *) &sock_address, sizeof(sock_address)) == -1)
		err("Failed to connect to the socket.\n");

	argc--, argv++;
	int msg_len = 0;

	for (int offset = 0, rem = sizeof(msg), n = 0; argc > 0 && rem > 0; offset += n, rem -= n, argc--, argv++) {
		n = snprintf(msg + offset, rem, "%s%c", *argv, 0);
		msg_len += n;
	}

	if (send(fd, msg, msg_len, 0) == -1)
		err("Failed to send the data.\n");

	int ret = 0, nb;
	while ((nb = recv(fd, rsp, sizeof(rsp), 0)) > 0) {
		if (nb == 1 && rsp[0] < MSG_LENGTH) {
			ret = rsp[0];
			if (ret == MSG_UNKNOWN) {
				warn("Unknown command.\n");
			} else if (ret == MSG_SYNTAX) {
				warn("Invalid syntax.\n");
			}
		} else {
			int end = MIN(nb, (int) sizeof(rsp) - 1);
			rsp[end--] = '\0';
			while (end >= 0 && isspace(rsp[end]))
				rsp[end--] = '\0';
			printf("%s\n", rsp);
			fflush(stdout);
		}
	}

	close(fd);
	return ret;
}
