readline_restart(FILE *ibuf, char **linebuf, size_t *linesize, size_t n)
{
	long sz;

	clearerr(ibuf);


	if (fileno(ibuf) == 0 && is_a_tty[0]) {
		if (*linebuf == NULL || *linesize < LINESIZE + n + 1)
			*linebuf = srealloc(*linebuf,
					*linesize = LINESIZE + n + 1);
		for (;;) {
			if (n >= *linesize - 128)
				*linebuf = srealloc(*linebuf, *linesize += 256);
again:
			sz = read(0, *linebuf + n, *linesize - n - 1);
			if (sz > 0) {
				n += sz;
				(*linebuf)[n] = '\0';
				if (n > 0 && (*linebuf)[n - 1] == '\n')
					break;
			} else {
				if (sz < 0 && errno == EINTR)
					goto again;
				if (n > 0) {
					if ((*linebuf)[n - 1] != '\n') {
						(*linebuf)[n++] = '\n';
						(*linebuf)[n] = '\0';
					}
					break;
				} else
					return -1;
			}
		}
	} else {


		if (fgetline_byone(linebuf, linesize, &n, ibuf, 1, n) == NULL)
			return -1;
	}
	if (n > 0 && (*linebuf)[n - 1] == '\n')
		(*linebuf)[--n] = '\0';
	return n;
}
