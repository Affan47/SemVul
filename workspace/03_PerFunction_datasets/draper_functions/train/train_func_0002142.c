_init_server (glibtop *server, const unsigned features)
{
	char *command, *temp;


	if (server->server_command == NULL) {
		const char *temp = getenv ("LIBGTOP_SERVER") ?
			getenv ("LIBGTOP_SERVER") : LIBGTOP_SERVER;

		server->server_command = g_strdup (temp);
	}

	if (server->server_rsh == NULL) {
		const char *temp = getenv ("LIBGTOP_RSH") ?
			getenv ("LIBGTOP_RSH") : "/usr/bin/ssh";

		server->server_rsh = g_strdup (temp);
	}


	if (server->method) return;


	if (server->server_command [0] != ':') {
		if (features & glibtop_server_features) {

			server->method = GLIBTOP_METHOD_PIPE;
		} else {


			server->method = GLIBTOP_METHOD_DIRECT;
		}

		return;
	}


	command = g_strdup (server->server_command+1);
	temp = strstr (command, ":");
	if (temp) *temp = 0;


	if (!strcmp (command, "direct")) {


		server->method = GLIBTOP_METHOD_DIRECT;

	} else if (!strcmp (command, "inet")) {

		server->method = GLIBTOP_METHOD_INET;


		if (temp == NULL) {

			if (server->server_host == NULL)
				server->server_host = g_strdup ("localhost");
		} else {
			char *temp2 = strstr (temp+1, ":");
			if (temp2) *temp2 = 0;


			if (server->server_host)
				g_free ((char *) server->server_host);

			server->server_host = g_strdup (temp+1);

			temp = temp2;
		}

		if (temp == NULL) {

			if (server->server_port == 0)
				server->server_port = DEFAULT_PORT;
		} else {
			char *temp2 = strstr (temp+1, ":");
			if (temp2) *temp2 = 0;

			if (sscanf (temp+1, "%ld", &server->server_port) != 1)
				server->server_port = DEFAULT_PORT;

			temp = temp2 ? temp2 + 1 : temp2;
		}

	} else if (!strcmp (command, "unix")) {


		server->method = GLIBTOP_METHOD_UNIX;

	} else if (!strcmp (command, "pipe")) {


		server->method = GLIBTOP_METHOD_PIPE;

	} else {

		glibtop_error_r (server, "Unknown server method '%s'",
				 server->server_command+1);

	}

	g_free (command);
}
