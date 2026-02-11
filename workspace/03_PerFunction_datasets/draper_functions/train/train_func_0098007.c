read_pty_proc(fd)
register int	fd;
{
	register Process	p;
	int	n;
	char	ibuf[1024+1];

	for (p = procs; ; p = p->p_next) {
		if (p == NULL) {
			writef("\riproc: unknown fd %d", fd);
			return;
		}
		if (p->p_fd == fd)
			break;
	}

	n = read(fd, (UnivPtr) ibuf, sizeof(ibuf) - 1);
	if (n <= 0) {
		if (n < 0) {
			switch (errno) {
			case EIO:
			case EWOULDBLOCK:
#if EWOULDBLOCK != EAGAIN
			case EAGAIN:
#endif


				if (p->p_io_state == IO_NEW)
					return;


				break;
			default:

				swritef(ibuf, sizeof(ibuf),
					"\n[pty read error: %s]\n", strerror(errno));
				proc_rec(p, ibuf, strlen(ibuf));

			}
		}
		proc_close(p);
	} else {
		if (p->p_io_state == IO_NEW) {
			p->p_io_state = IO_RUNNING;
			UpdModLine = YES;
		}
		proc_rec(p, ibuf, (size_t)n);
	}
}
