vfile_try_open(int flags, mode_t mode, va_list ap)
{
	int fd;
	const char *filename;

	while ((filename = va_arg(ap, const char *)))
	{
		fd = open(filename, flags, mode);
		if (fd >= 0)
		{
			println("filename = %s", filename);
			return fd;
		}
	}

	return -ENOENT;
}
