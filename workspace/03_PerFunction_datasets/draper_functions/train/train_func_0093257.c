new_session(unsigned char *_remote_node,
			       char *service, char *port,
			       unsigned char c)
{
    credit = c;
    strcpy(remote_service, service);
    strcpy(remote_port, port);

    if (!client_session) return -1;

    debuglog(("starting queued session: credit = %d\n", c));
    strcpy(remote_node, (char *)_remote_node);

    if (master_fd != -1)
    {
	fcntl(master_fd, F_SETFL, fcntl(master_fd, F_GETFL, 0) | O_NONBLOCK);
	connected = true;

	send_login_response();
	client_session->start_port();
    }
    else
    {
	return -1;
    }
    return 0;
}
