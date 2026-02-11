gg_dcc_socket_create(uin_t uin, uint16_t port)
{
	struct gg_dcc *c;
	struct sockaddr_in sin;
	int sock, bound = 0, errno2;

	gg_debug(GG_DEBUG_FUNCTION, "** gg_create_dcc_socket(%d, %d);\n", uin, port);

	if (!uin) {
		gg_debug(GG_DEBUG_MISC, "// gg_create_dcc_socket() invalid arguments\n");
		errno = EINVAL;
		return NULL;
	}

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		gg_debug(GG_DEBUG_MISC, "// gg_create_dcc_socket() can't create socket (%s)\n", strerror(errno));
		return NULL;
	}

	if (port == 0 || port == -1)
		port = GG_DEFAULT_DCC_PORT;

	while (!bound) {
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(port);

		gg_debug(GG_DEBUG_MISC, "// gg_create_dcc_socket() trying port %d\n", port);
		if (!bind(sock, (struct sockaddr*) &sin, sizeof(sin)))
			bound = 1;
		else {
			if (++port == 65535) {
				gg_debug(GG_DEBUG_MISC, "// gg_create_dcc_socket() no free port found\n");
				close(sock);
				return NULL;
			}
		}
	}

	if (listen(sock, 10)) {
		gg_debug(GG_DEBUG_MISC, "// gg_create_dcc_socket() unable to listen (%s)\n", strerror(errno));
		errno2 = errno;
		close(sock);
		errno = errno2;
		return NULL;
	}

	gg_debug(GG_DEBUG_MISC, "// gg_create_dcc_socket() bound to port %d\n", port);

	if (!(c = malloc(sizeof(*c)))) {
		gg_debug(GG_DEBUG_MISC, "// gg_create_dcc_socket() not enough memory for struct\n");
		close(sock);
		return NULL;
	}
	memset(c, 0, sizeof(*c));

	c->port = c->id = port;
	c->fd = sock;
	c->type = GG_SESSION_DCC_SOCKET;
	c->uin = uin;
	c->timeout = -1;
	c->state = GG_STATE_LISTENING;
	c->check = GG_CHECK_READ;
	c->callback = gg_dcc_callback;
	c->destroy = gg_dcc_free;

	return c;
}
