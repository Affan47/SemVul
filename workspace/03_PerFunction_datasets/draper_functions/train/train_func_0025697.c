cmd_connect(int listenfd, short evtype, void *arg)
{
	struct sockaddr_in6 remote_addr;
	socklen_t addrlen = sizeof(remote_addr);
	int sockfd;
	int i;

	if(!(evtype & EV_READ)) {
		ERROR_OUT("Unknown event type in connect callback: 0x%hx\n", evtype);
		return;
	}


	for(i = 0; i < 10; i++) {
		sockfd = accept(listenfd, (struct sockaddr *)&remote_addr, &addrlen);
		if(sockfd < 0) {
			if(errno != EWOULDBLOCK && errno != EAGAIN) {
				ERRNO_OUT("Error accepting an incoming connection");
			}
			break;
		}

		INFO_OUT("Client connected on fd %d\n", sockfd);

		setup_connection(sockfd, &remote_addr, (struct event_base *)arg);
	}
}
