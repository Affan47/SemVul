_crywrap_remote_connect(const struct sockaddr_storage *addr, int port)
{
	struct addrinfo *cur;
	int sock;

	cur = calloc(1, sizeof(struct addrinfo));
	if (cur == NULL)
		return -1;

	cur->ai_family = addr->ss_family;

	switch (cur->ai_family) {
	case AF_INET6:
		cur->ai_addrlen = sizeof(struct sockaddr_in6);
		break;
	case AF_INET:
		cur->ai_addrlen = sizeof(struct sockaddr_in);
		break;
	}

	cur->ai_addr = malloc(cur->ai_addrlen);
	if (cur->ai_addr == NULL)
		return -1;

	memcpy(cur->ai_addr, addr, cur->ai_addrlen);

	switch (cur->ai_family) {
	case AF_INET6:
		((struct sockaddr_in6 *) (cur->ai_addr))->sin6_port = port;
		break;
	case AF_INET:
		((struct sockaddr_in *) (cur->ai_addr))->sin_port = port;
		break;
	}

	sock = socket(cur->ai_family, SOCK_STREAM, IPPROTO_IP);
	if (sock < 0) {
		cry_error("socket(): %s", strerror(errno));
		exit(1);
	}

	if (connect(sock, cur->ai_addr, cur->ai_addrlen) < 0) {
		cry_error("connect(): %s", strerror(errno));
		exit(1);
	}

	free(cur->ai_addr);
	free(cur);

	return sock;
}
