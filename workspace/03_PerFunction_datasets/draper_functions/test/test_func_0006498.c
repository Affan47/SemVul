screendump(int vcnum, FILE * F)
{
	char infile[MAXPATHLEN];
	unsigned char header[4];
	unsigned int rows, cols;
	int fd;
	size_t i, j;
	char *inbuf, *outbuf, *p, *q;

	sprintf(infile, "/dev/vcsa%d", vcnum);
	fd = open(infile, O_RDONLY);
	if (fd < 0 && vcnum == 0) {

		sprintf(infile, "/dev/vcsa");
		fd = open(infile, O_RDONLY);
	}
	if (fd < 0) {


		sprintf(infile, "/dev/vcc/a%.0u", vcnum);
		fd = open(infile, O_RDONLY);
	}
	if (fd < 0) {
		sprintf(infile, "/dev/vcsa%d", vcnum);
		goto read_error;
	}
	if (read(fd, header, 4) != 4)
		goto read_error;
	rows = header[0];
	cols = header[1];
	if (rows * cols == 0)
		goto read_error;

	inbuf = xmalloc(rows * cols * 2);
	outbuf = xmalloc(rows * (cols + 1));

	if (read(fd, inbuf, rows * cols * 2) != rows * cols * 2)
		goto read_error;
	p = inbuf;
	q = outbuf;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			*q++ = *p;
			p += 2;
		}
		while (j-- > 0 && q[-1] == ' ')
			q--;
		*q++ = '\n';
	}
	if (fwrite(outbuf, 1, q - outbuf, F) != (size_t) (q - outbuf)) {
		warnx(_("Error writing screendump"));
		goto error;
	}
	close(fd);
	return;

      read_error:
	warnx(_("Couldn't read %s"), infile);
      error:
	if (fd >= 0)
		close(fd);
	exit(EXIT_FAILURE);
}
