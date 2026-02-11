accept_connection(struct sockaddr_in *address, int tcpsock, int udpsock)
{
	fd_set readfds;
	int conn;
	int addrlen = sizeof(struct sockaddr_in);

	if(address == NULL || tcpsock < 0)
		return FALSE;

	while(TRUE) {
		if(!gconf.inetd) {
			FD_ZERO(&readfds);
			FD_SET(tcpsock, &readfds);
			FD_SET(udpsock, &readfds);
			conn = select(max(tcpsock, udpsock) + 1, &readfds,
				      NULL, NULL, NULL);
			if(conn < 0 && errno == EINTR)
				continue;
			else if(conn < 0)
				die("select()\n");

			if(FD_ISSET(udpsock, &readfds))
				getudpmessage(udpsock);

			if(!FD_ISSET(tcpsock, &readfds))
				continue;

			if((conn = accept(tcpsock, (struct sockaddr *)address,
					  &addrlen)) < 0) {
				if(errno == EINTR)
					continue;
				else
					die("accept");
			}

			break;

		} else {
			conn = 0;
			getpeername(0, (struct sockaddr *)address, &addrlen);
			break;
		}
	}

	return conn;
}
