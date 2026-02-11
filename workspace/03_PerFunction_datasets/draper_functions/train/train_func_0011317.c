handle_client(int client_socket) {
	static FILE * fd = NULL;
	int disconnect = 0;

	if (!fd)
		fd = fdopen(client_socket, "rw");

	signal(SIGPIPE, SIG_IGN);

	if(fd != NULL && !feof(fd)) {
		debug("client socket is ok and readable: %i\n", client_socket);
		char line[BUFSIZE];

		if(fgets(line, sizeof(line), fd) == NULL) {
			disconnect = 1;
		}
		else {
			if(!ferror(fd)) {
				unsigned chunks, i;
				char ** lines = split(line, "\n", & chunks);

				for(i = 0; i < chunks && !disconnect; ++i) {
					char reply[BUFSIZE] = { 0, };
					debug("client message: <%s>\n", lines[i]);

					disconnect = execcmd(lines[i], reply);

					if(strlen(reply)) {
						strncat(reply, "\n", BUFSIZE - strlen(reply));
						write(client_socket, reply, strlen(reply));
					}
				}
			}

			else {
				debug("fd error: %i\n", ferror(fd));
				disconnect = 1;
			}

		}
	}

	if(disconnect) {
		debug("removing client\n");
		shutdown(SHUT_RDWR, client_socket);
		close(client_socket);
		fclose(fd);

		remove_handle(client_socket);
	}
}
