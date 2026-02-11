mwrite(int fd, const void *buf, size_t count)
{
int	n;

	while ((n=write(fd, buf, count)) < 0 && errno == EINTR)
		;
	return (n);
}
