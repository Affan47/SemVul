DoListen(struct PortInfo *portptr)
{
	struct addrinfo hints;
	struct addrinfo *res, *res_o;
	int error;
	char port[MAXLINE];


	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	ircsprintf(port, "%d", portptr->port);
	error = getaddrinfo(LocalHostName, port, &hints, &res);

	res_o = res;

	if (error)
	{
		putlog(LOG1,
		       "Unable to get local addresses, this should never happen: %s",
		       gai_strerror(error));
		return;
	}

	while (res != NULL)
	{
		if ((portptr->socket = socket(res->ai_family, SOCK_STREAM, 6)) == -1)
		{
			res = res->ai_next;
			portptr->socket = NOSOCKET;
			continue;
		}


		SetSocketOptions(portptr->socket);
		SetPort((struct sockaddr *)res->ai_addr, portptr->port);

		if (bind(portptr->socket, res->ai_addr, res->ai_addrlen) == -1)
		{
			putlog(LOG1, "FATAL: Unable to bind port tcp/%d: %s",
			       portptr->port, strerror(errno));
			close(portptr->socket);
			portptr->socket = NOSOCKET;
		}
		else
#ifdef SOMAXCONN
			if (listen(portptr->socket, SOMAXCONN) == -1)
#else

			if (listen(portptr->socket, HYBSERV_SOMAXCONN) == -1)
#endif

			{
				putlog(LOG1, "Unable to listen on port tcp/%d: %s",
				       portptr->port, strerror(errno));
				close(portptr->socket);
				portptr->socket = NOSOCKET;
			}
			else
			{
				putlog(LOG1,
				       "Listener successfully started on host [%s] port tcp/%d",
				       (LocalHostName != NULL) ? LocalHostName : "*",
				       portptr->port);
			}

		res = res->ai_next;
	}

	portptr->tries++;

	if (res_o != NULL)
		freeaddrinfo(res_o);
}
