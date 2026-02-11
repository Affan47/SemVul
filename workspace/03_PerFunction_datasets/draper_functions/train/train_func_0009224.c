ldns_sock_wait(int sockfd, struct timeval timeout, int write)
{
	int ret;
#ifndef S_SPLINT_S
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(FD_SET_T sockfd, &fds);
	if(write)
		ret = select(sockfd+1, NULL, &fds, NULL, &timeout);
	else
		ret = select(sockfd+1, &fds, NULL, NULL, &timeout);
#endif
	if(ret == 0)

		return 0;
	else if(ret == -1)

		return 0;
	return 1;
}
