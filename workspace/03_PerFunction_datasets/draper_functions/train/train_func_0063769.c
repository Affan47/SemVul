mvapich_read_n (mvapich_state_t *st,  struct mvapich_info *mvi,
		void *buf, size_t len)
{
	int nleft = len;
	int n = 0;
	unsigned char * p = buf;

	while (nleft > 0) {

		if (mvapich_poll (st, mvi, 0) < 0)
			return (-1);

		if ((n = read (mvi->fd, p, nleft)) < 0) {
			if (errno == EAGAIN || errno == EINTR)
				continue;
			return (-1);
		}

		if (n == 0) {
			error ("mvapich: rank %d: "
					"Unexpected EOF (%dB left to read)",
					mvi->rank, nleft);
			return (-1);
		}

		nleft -= n;
		p += n;
	}

	return (len - nleft);
}
