control(const char *a)
{
	int fd, r, l;


	fd = open("supervise/control", O_WRONLY|O_NDELAY);
	if (fd == -1) {
		if (errno != ENODEV)
			warn("can't open supervise/control");
		else
			*a == 'x' ? ok("runsv not running") : failx("runsv not running");
		return -1;
	}
	l = strlen(a);
	r = write(fd, a, l);
	close(fd);
	if (r != l) {
		warn("can't write to supervise/control");
		return -1;
	}
	return 1;
}
