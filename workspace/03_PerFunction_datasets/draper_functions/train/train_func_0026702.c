open_log(const char *w_arg, int a_flag)
{
	int fd, flags;

	flags = (a_flag ? O_APPEND : O_TRUNC) | O_WRONLY | O_CREAT;
#ifdef O_LARGEFILE
	flags |= O_LARGEFILE;
#endif
	if (!strcmp(w_arg, "-"))
		fd = STDOUT_FILENO;
	else
		fd = open(w_arg, flags, 0644);
	if (fd < 0) {
		perror(w_arg);
		exit(1);
	}
	return (fd);
}
