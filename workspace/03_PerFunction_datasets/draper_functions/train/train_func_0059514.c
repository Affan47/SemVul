fcntl(int fd, int cmd, ...)
{
	va_list args;
	void *arg;

	if (!initialized)
		initialize();

	va_start(args, cmd);
	arg = va_arg(args, void *);
	va_end(args);
	if (! is_oss_device(fd))
		return _fcntl(fd, cmd, arg);
	else
		return ops[fds[fd]->class].fcntl(fd, cmd, arg);
}
