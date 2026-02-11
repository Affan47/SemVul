file_noperation_ro(const char *filename, size_t size, int (*handle)(int fd, size_t size))
{
	int fd;
	int ret;

	fd = file_open_ro(filename);
	if (fd < 0)
	{
		pr_error_info("open file %s", filename);
		return fd;
	}

	ret = handle(fd, size);

	close(fd);

	return ret;
}
