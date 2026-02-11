show_associated_loop_devices(char *filename, unsigned long long offset, int isoff)
{
	struct looplist ll;
	struct stat filestat;
	int fd;

	if (stat(filename, &filestat) == -1) {
		perror(filename);
		return 1;
	}

	if (looplist_open(&ll, LLFLG_USEDONLY) == -1) {
		error(_("%s: /dev directory does not exist."), progname);
		return 1;
	}

	while((fd = looplist_next(&ll)) != -1) {
		if (is_associated(fd, &filestat, offset, isoff) == 1)
			show_loop_fd(fd, ll.name);
		close(fd);
	}
	looplist_close(&ll);

	return 0;
}
