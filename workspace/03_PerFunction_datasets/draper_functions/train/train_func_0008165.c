wall_main(int argc UNUSED_PARAM, char **argv)
{
	struct utmp *ut;
	char *msg;
	int fd = argv[1] ? xopen(argv[1], O_RDONLY) : STDIN_FILENO;

	msg = xmalloc_read(fd, NULL);
	if (ENABLE_FEATURE_CLEAN_UP && argv[1])
		close(fd);
	setutent();
	while ((ut = getutent()) != NULL) {
		char *line;
		if (ut->ut_type != USER_PROCESS)
			continue;
		line = concat_path_file("/dev", ut->ut_line);
		xopen_xwrite_close(line, msg);
		free(line);
	}
	if (ENABLE_FEATURE_CLEAN_UP) {
		endutent();
		free(msg);
	}
	return EXIT_SUCCESS;
}
