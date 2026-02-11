fd_first_available(void)
{
	int fd;

	fd = open("/dev/null", O_RDWR, 0);
	if (-1 == fd)
		g_error("%s() failed to open /dev/null: %m", G_STRFUNC);
	close(fd);

	return fd;
}
