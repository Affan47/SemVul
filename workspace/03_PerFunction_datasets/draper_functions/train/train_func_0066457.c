read_file(char *filename, char **bufp)
{
	gfarm_error_t e;
	int fd;
	struct stat st;
	ssize_t sz, msg_sz = 0;
	char *buf = NULL;
	size_t allocsz;
	int overflow;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (gfarm_errno_to_error(errno));

	if (fstat(fd, &st) != 0)
		e = gfarm_errno_to_error(errno);
	else {
		overflow = 0;
		allocsz = gfarm_size_add(&overflow, st.st_size, 1);
		if (!overflow)
			buf = malloc(allocsz);
		if (buf != NULL) {
			while ((sz = read(fd, buf + msg_sz, st.st_size - msg_sz)) > 0) {
				msg_sz += sz;
			}
			if (sz == 0) {
				buf[msg_sz] = '\0';
				*bufp = buf;
				e = GFARM_ERR_NO_ERROR;
			} else
				e = gfarm_errno_to_error(errno);
		} else
			e = GFARM_ERR_NO_MEMORY;
	}

	close(fd);

	return e;
}
