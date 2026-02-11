preadfd(void)
{
	int nr;
	char *buf =  parsefile->buf;
	parsenextc = buf;

retry:
#ifndef SMALL
	if (parsefile->fd == 0 && el) {
		static const char *rl_cp;
		static int el_len;

		if (rl_cp == NULL)
			rl_cp = el_gets(el, &el_len);
		if (rl_cp == NULL)
			nr = 0;
		else {
			nr = el_len;
			if (nr > IBUFSIZ - 1)
				nr = IBUFSIZ - 1;
			memcpy(buf, rl_cp, nr);
			if (nr != el_len) {
				el_len -= nr;
				rl_cp += nr;
			} else
				rl_cp = 0;
		}

	} else
#endif

#ifdef HETIO
		nr = hetio_read_input(parsefile->fd);
		if (nr == -255)
#endif
		nr = read(parsefile->fd, buf, IBUFSIZ - 1);


	if (nr < 0) {
		if (errno == EINTR)
			goto retry;
		if (parsefile->fd == 0 && errno == EWOULDBLOCK) {
			int flags = fcntl(0, F_GETFL, 0);
			if (flags >= 0 && flags & O_NONBLOCK) {
				flags &=~ O_NONBLOCK;
				if (fcntl(0, F_SETFL, flags) >= 0) {
					out2str("sh: turning off NDELAY mode\n");
					goto retry;
				}
			}
		}
	}
	return nr;
}
