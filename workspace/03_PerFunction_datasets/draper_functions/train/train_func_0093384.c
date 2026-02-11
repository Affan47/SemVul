savepid(void)
{
	int	fd;
	char	buf[40];

	if  ((fd = open(PIDFILE, O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0)
		return;
	sprintf(buf, "%d\n", getpid());
	write(fd, buf, strlen(buf));
	close(fd);
}
