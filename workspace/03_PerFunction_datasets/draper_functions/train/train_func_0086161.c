remote_socket_options(int sockfd)
{
	int rcvbuf, optlen;

	pc->rcvbufsize = rcvbuf = READBUFSIZE;

	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (char *)&rcvbuf,
	    sizeof(rcvbuf)) < 0) {
		error(INFO, "SO_RCVBUF setsockopt error\n");
		return;
	}

	optlen = sizeof(rcvbuf);
        if (getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (char *)&rcvbuf,
            (socklen_t *)&optlen) < 0) {
                error(INFO, "SO_RCVBUF getsockopt error\n");
                return;
        }

	if (CRASHDEBUG(1))
        	printf("socket SO_RCVBUF size: %d\n", rcvbuf);

	rcvbuf = 1;

        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVLOWAT, (char *)&rcvbuf,
            sizeof(rcvbuf)) < 0) {


		if (CRASHDEBUG(1))
                	error(INFO, "SO_RCVLOWAT setsockopt error: %s\n",
				strerror(errno));
		rcvbuf = 0;
        }

        optlen = sizeof(rcvbuf);
        if (getsockopt(sockfd, SOL_SOCKET, SO_RCVLOWAT, (char *)&rcvbuf,
            (socklen_t *)&optlen) < 0) {
                error(INFO, "SO_RCVLOWAT getsockopt error\n");
                return;
        }

	if (CRASHDEBUG(1) || (rcvbuf != 1))
        	error(INFO, "socket SO_RCVLOWAT value: %d\n", rcvbuf);

}
