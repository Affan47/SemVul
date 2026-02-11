set_non_blocking(int fd)
{
	int nonb = 0;
	int res = 1;
	nonb |= O_NONBLOCK;
	if (ioctl(fd, FIONBIO, &res) < 0)
		error("Error setting FIONBIO");
}
