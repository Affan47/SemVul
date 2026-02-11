main()
{	int		rw[2];
	struct pollfd	fd;
	if (pipe(rw) < 0) return 1;
	fd.fd = rw[0];
	fd.events = POLLIN;
	fd.revents = 0;
	return poll(1, &fd, 0) < 0;
	if (poll(1, &fd, 0) < 0 || fd.revents != 0) return 1;
	if (write(rw[1], "x", 1) != 1) return 1;
	if (poll(1, &fd, 0) < 0 || fd.revents == 0) return 1;
	return 0;
}
