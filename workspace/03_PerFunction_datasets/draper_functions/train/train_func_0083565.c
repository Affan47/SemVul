server_open(SERVER *server, struct SERV_ADDR *addr, int tell)
{
    long	tmp;

    server_close(server);
    server->fd = open_socket();
    if (server->fd < 0) {
	set_message("Error: Failed to create socket!", True);
	return -1;
    }

    if (tell > 1)
	set_message("Server contacted, waiting for response...", False);

    tmp = connect_socket(server->fd, addr);

    if (tmp < 0 && would_block(server->fd, errno)) {
	if (tell == 0)
	    return 0;

	tmp = 0;
	do_wait(&server->fd, True, server->quit_func, server);
	if (server->fd < 0)
	    return -1;
    }

    server->buffer[0] = '\0';
    if (tmp >= 0)
	do {
	    tmp = read(server->fd, server->buffer, server->len);
	} while (tmp < 0 && errno == EINTR);

    if (tmp >= 0) {
	server->buffer[tmp] = '\0';
	return 0;
    }

    if (would_block(server->fd, errno))
	return 0;

    perror("knews: read");

    if (tell) {
	char	message[128];
	char	*tmp = error_string(errno);

	if (!tmp)
	    tmp = "Connection failed";
	sprintf(message, "Error: %s!", tmp);
	set_message(message, True);
    }

    return -1;
}
