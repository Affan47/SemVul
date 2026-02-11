roll_file(const char *filename, off_t *size)
{
	char buf[BUFSIZ];
	int fd;
	struct stat st;
	off_t pos;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		err(EXIT_FAILURE, _("cannot open \"%s\" for read"), filename);

	if (fstat(fd, &st) == -1)
		err(EXIT_FAILURE, _("cannot stat \"%s\""), filename);

	if (st.st_size == *size) {
		close(fd);
		return;
	}

	if (lseek(fd, *size, SEEK_SET) != (off_t)-1) {
		ssize_t rc, wc;

		while ((rc = read(fd, buf, sizeof(buf))) > 0) {
			wc = write(STDOUT_FILENO, buf, rc);
			if (rc != wc)
				warnx(_("incomplete write to \"%s\" (written %zd, expected %zd)\n"),
					filename, wc, rc);
		}
		fflush(stdout);
	}

	pos = lseek(fd, 0, SEEK_CUR);


	*size = (pos != -1 && pos != *size) ? pos : st.st_size;

	close(fd);
}
