file_ncrc32_seek(const char *file_name, off_t offset, int whence, size_t size, u32 *crc)
{
	int fd;
	int ret;

	fd = open(file_name, READ_FLAGS);
	if (fd < 0)
	{
		pr_error_info("open \"%s\"", file_name);
		return -1;
	}

	ret = ffile_ncrc32_seek(fd, offset, whence, size, crc);
	if (ret < 0)
	{
		error_msg("ffile_ncrc32_seek");
	}

	close(fd);

	return ret;
}
