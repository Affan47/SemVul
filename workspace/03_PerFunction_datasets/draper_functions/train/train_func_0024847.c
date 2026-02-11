clamd_verify_email(const gchar* path, response* result) {
	gchar buf[BUFSIZ];
	int n_read;
	gchar* command;
	Clamd_Stat stat;


	if (!result) {
		result = malloc(sizeof(response));
		memset(result, '\0', sizeof(response));
	}
	create_socket();
	if (sock < 0) {
		debug_print("no connection\n");
		return NO_CONNECTION;
	}
	memset(buf, '\0', sizeof(buf));
	if (Socket->type == INET_SOCKET) {
		gchar* tmp = g_new0(gchar, BUFSIZ);
		stat = clamd_stream_scan(path, &tmp, BUFSIZ);
		if (stat != OK) {
			close_socket();
			result->msg = g_strdup(tmp);
			g_free(tmp);
			debug_print("result: %s\n", result->msg);

			return stat;
		}
		debug_print("copy to buf: %s\n", tmp);
		memcpy(&buf, tmp, BUFSIZ);
		g_free(tmp);
	}
	else {
		command = g_strconcat(scan, " ", path, "\n", NULL);
		debug_print("command: %s\n", command);
		if (write(sock, command, strlen(command)) == -1) {
			debug_print("no connection\n");
			stat = NO_CONNECTION;
		}
		g_free(command);
		memset(buf, '\0', sizeof(buf));
		while ((n_read = read(sock, buf, BUFSIZ)) > 0) {
			if (buf[strlen(buf) - 1] == '\n')
				buf[strlen(buf) - 1] = '\0';
		}
	}
	debug_print("response: %s\n", buf);
	if (strstr(buf, "ERROR")) {
		stat = SCAN_ERROR;
		result->msg = g_strdup(buf);
	}
	else if (strstr(buf, "FOUND")) {
		stat = VIRUS;
		result->msg = g_strdup(buf);
	}
	else {
		stat = OK;
		result->msg = NULL;
	}
	close_socket();


	return stat;
}
