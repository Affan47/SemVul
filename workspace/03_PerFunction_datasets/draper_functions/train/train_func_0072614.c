try_dotlock(const char *tmpname,
		       const char *dotlock,
		       char *idbuf)
{
	struct stat stat_buf;

	int fd;

	fd=open(tmpname, O_RDWR | O_CREAT, 0644);

	if (fd < 0)
		return (-1);

	if (writeid(idbuf, fd))
	{
		close(fd);
		unlink(tmpname);
		return (-1);
	}
	close(fd);

	if (link(tmpname, dotlock) < 0 || stat(tmpname, &stat_buf) ||
	    stat_buf.st_nlink != 2)
	{
		if (errno != EEXIST)
			errno=EIO;

		unlink(tmpname);
		return (-1);
	}
	unlink(tmpname);
	return (0);
}
