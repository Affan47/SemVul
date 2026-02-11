file_read(ang_file *f, char *buf, size_t n)
{
	int fd = fileno(f->fh);
	int ret;
	int n_read = 0;

#ifndef SET_UID

	while (n >= READ_BUF_SIZE)
	{
		ret = read(fd, buf, READ_BUF_SIZE);
		n_read += ret;

		if (ret == -1)
			return -1;
		else if (ret != READ_BUF_SIZE)
			return n_read;

		buf += READ_BUF_SIZE;
		n -= READ_BUF_SIZE;
	}

#endif

	ret = read(fd, buf, n);
	n_read += ret;

	if (ret == -1)
		return -1;
	else
		return n_read;
}
