network_check_accept(int *fd)
{
	int status;
	fd_set set;
	struct timeval tv;

	FD_ZERO(&set);
	FD_SET(*fd, &set);
	tv.tv_sec = tv.tv_usec = 0;

	if(!select((*fd)+1, &set, NULL, NULL, &tv))
		return 0;

	status = accept(*fd, NULL, 0);
	TRACE("Accept returned %d\n", status);

	if(status == -1) {
		TRACE("Error condition is %d\n", errno);
		perror("accept:");
		return 0;
	}


	close(*fd);
	*fd = status;
	fcntl(*fd, F_SETFL, O_NONBLOCK);


	send(*fd, "\xff\xfb\x01\xff\xfb\x03\xff\xfd\x0f3", 9, 0);

	return 1;
}
