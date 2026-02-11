open64(const char *file, int oflag, ...)
{
	int fd;

	if (oflag & O_CREAT) {
		va_list ap;
		mode_t mode;

		va_start(ap, oflag);
		mode = va_arg(ap, mode_t);

		fd = v4l1_open(file, oflag | O_LARGEFILE, mode);

		va_end(ap);
	} else
		fd = v4l1_open(file, oflag | O_LARGEFILE);

	return fd;
}
