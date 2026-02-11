sock_poll_clients(void)
{
	struct timeval t;
	ClientSocketMap* clientSocket;

	debug(RPT_DEBUG, "%s()", __FUNCTION__);

	t.tv_sec = 0;
	t.tv_usec = 0;


	read_fd_set = active_fd_set;

	if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, &t) < 0) {
		report(RPT_ERR, "%s: Select error - %s",
			__FUNCTION__, sock_geterror());
		return -1;
	}


	LL_Rewind(openSocketList);
	for (clientSocket = (ClientSocketMap *) LL_Get(openSocketList);
	     clientSocket != NULL;
	     clientSocket = LL_GetNext(openSocketList)) {

		if (FD_ISSET(clientSocket->socket, &read_fd_set)) {
			if (clientSocket->socket == listening_fd) {

				Client *c;
				int new_sock;
				struct sockaddr_in clientname;
				socklen_t size = sizeof(clientname);

				new_sock = accept(listening_fd, (struct sockaddr *) &clientname, &size);
				if (new_sock < 0) {
					report(RPT_ERR, "%s: Accept error - %s",
						__FUNCTION__, sock_geterror());
					return -1;
				}
				report(RPT_NOTICE, "Connect from host %s:%hu on socket %i",
					inet_ntoa(clientname.sin_addr), ntohs(clientname.sin_port), new_sock);
				FD_SET(new_sock, &active_fd_set);

				fcntl(new_sock, F_SETFL, O_NONBLOCK);


				if ((c = client_create(new_sock)) == NULL) {
					report(RPT_ERR, "%s: Error creating client on socket %i - %s",
						__FUNCTION__, clientSocket->socket, sock_geterror());
					return -1;
				}
				else {

					ClientSocketMap *newClientSocket;
					newClientSocket = (ClientSocketMap *) LL_Pop(freeClientSocketList);
					if (newClientSocket != NULL) {
						newClientSocket->socket = new_sock;
						newClientSocket->client = c;
						LL_InsertNode(openSocketList, (void *) newClientSocket);

						LL_Next(openSocketList);
					}
					else {
						report(RPT_ERR, "%s: Error - free client socket list exhausted - %d clients.",
							__FUNCTION__, FD_SETSIZE);
						return -1;
					}
				}
				if (clients_add_client(c) == NULL) {
					report(RPT_ERR, "%s: Could not add client on socket %i",
						 __FUNCTION__, clientSocket->socket);
					return -1;
				}
			}
			else {
				int err = 0;
				debug(RPT_DEBUG, "%s: reading...", __FUNCTION__);
				err = sock_read_from_client(clientSocket);
				debug(RPT_DEBUG, "%s: ...done", __FUNCTION__);
				if (err < 0)
					sock_destroy_socket();
			}
		}
	}
	return 0;
}
