getblock(atl)
daddr	atl;
{
	int	bno,
		off;
	static int	curblock = -1;

	bno = da_to_bno(atl);
	off = da_to_off(atl);
	nleft = JBUFSIZ - off;

	if (bno != curblock) {
		ssize_t r;
		char *what;

		errno = 0;
		what = "lseek";
		lseek(data_fd, (off_t) bno * JBUFSIZ, L_SET);
		if (errno == 0) {
			what = "read";
			r = read(data_fd, (UnivPtr)blk_buf, (size_t)JBUFSIZ);
			if (errno == 0 && r != JBUFSIZ) {
				fprintf(stderr, "read of JOVE tempfile failed -- too short\n");
				exit(1);
			}
		}
		if (errno != 0) {
			fprintf(stderr, "%s of JOVE tempfile failed %s\n", what, strerror(errno));
			exit(1);
		}
		curblock = bno;
	}
	return blk_buf + off;
}
