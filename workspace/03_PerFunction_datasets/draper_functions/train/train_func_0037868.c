p_open(const char *path, volatile int flags, ...)
{
	mode_t mode = 0;

	if (flags & O_CREAT) {
		va_list arg_list;

		va_start(arg_list, flags);
		mode = (mode_t)va_arg(arg_list, int);
		va_end(arg_list);
	}

	return open(path, flags | O_BINARY | O_CLOEXEC, mode);
}
