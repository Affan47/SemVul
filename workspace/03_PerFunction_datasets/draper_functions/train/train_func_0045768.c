check_valid_formats(int fd, const char *file)
{
	int flags = 0;
	while (flags < ALLFLAGS)
		check_evemu_read(fd, file, flags++);
}
