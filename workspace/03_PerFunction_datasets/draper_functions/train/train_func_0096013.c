daemon_init()
{
	int fd;

	fd = open("/dev/null", O_RDWR);
	if (fd == -1)
		exit(-1);

	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	setsid();
	chdir("/");
}
