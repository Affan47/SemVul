urlclose(fd)
int fd;
{
	int n;

	n = Xclose(fd);
	if (_urlclose(fd, "close") < 0) n = -1;

	return(n);
}
