rb_setup_fd_sigio(rb_fde_t *F)
{
	int flags = 0;
	int fd = F->fd;
	flags = fcntl(fd, F_GETFL, 0);
	if(flags == -1)
		return 0;

	if(flags & O_ASYNC)
	{
		flags &= ~O_ASYNC;
		fcntl(fd, F_SETFL, flags);
	}

	flags |= O_ASYNC | O_NONBLOCK;

	if(fcntl(fd, F_SETFL, flags) == -1)
		return 0;

	if(fcntl(fd, F_SETSIG, RTSIGIO) == -1)
		return 0;
	if(fcntl(fd, F_SETOWN, getpid()) == -1)
		return 0;

	return 1;
}
