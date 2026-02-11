open_duplex(int *fd)
{
#if !defined(HAVE_SOCKETPAIR) || HAVE_SOCKETPAIR
    int	tmp;

    do {
	tmp = socketpair(PF_UNIX, SOCK_STREAM, 0, fd);
    } while (tmp < 0 && errno == EINTR);

    if (tmp < 0) {
	perror("knews: socketpair");
	return -1;
    }

    if (fcntl(fd[0], F_SETFD, FD_CLOEXEC) < 0)
	perror("fcntl");

    if (set_nonblock(fd[0]) < 0) {
	close(fd[0]);
	close(fd[1]);
	return -1;
    }

    return 0;
#else
    fputs("knews: compiled without HAVE_SOCKETPAIR, "
	  "can't open connection!\n", stderr);
    return -1;
#endif
}
