buffer_0_read (int fd, char *buf, int len)
{
	if (buffer_flush (buffer_1) == -1)
		return -1;
	return read (fd, buf, len);
}
