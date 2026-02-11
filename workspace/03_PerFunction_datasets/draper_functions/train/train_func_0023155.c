redirect(union node *redir, int flags)
{
	union node *n;
	struct redirtab *sv;
	int i;
	int fd;
	int newfd;
	int *p;
#if notyet
	char memory[10];

	for (i = 10 ; --i >= 0 ; )
		memory[i] = 0;
	memory[1] = flags & REDIR_BACKQ;
#endif
	if (!redir)
		return;
	sv = NULL;
	INTOFF;
	if (likely(flags & REDIR_PUSH))
		sv = redirlist;
	n = redir;
	do {
		newfd = openredirect(n);
		if (newfd < -1)
			continue;

		fd = n->nfile.fd;

		if (sv) {
			p = &sv->renamed[fd];
			i = *p;

			if (likely(i == EMPTY)) {
				i = CLOSED;
				if (fd != newfd) {
					i = savefd(fd, fd);
					fd = -1;
				}
			}

			if (i == newfd)

				i = REALLY_CLOSED;

			*p = i;
		}

		if (fd == newfd)
			continue;

#ifdef notyet
		dupredirect(n, newfd, memory);
#else
		dupredirect(n, newfd);
#endif
	} while ((n = n->nfile.next));
	INTON;
#ifdef notyet
	if (memory[1])
		out1 = &memout;
	if (memory[2])
		out2 = &memout;
#endif
	if (flags & REDIR_SAVEFD2 && sv->renamed[2] >= 0)
		preverrout.fd = sv->renamed[2];
}
