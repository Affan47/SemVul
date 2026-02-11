forward(con c, host h) {
	int fd;

	if (fd_count >= MAX_FDS ||
	    (fd = socket(h->ai->ai_family, h->ai->ai_socktype, h->ai->ai_protocol))
			< 0 || !prepare_sock(fd, 1))
		return closereq(c);

	if (connect(fd, h->ai->ai_addr, h->ai->ai_addrlen) &&
			errno != EINPROGRESS) {
		close(fd);
		return closereq(c);
	}

	ev[fd_count].fd = fd;
	ev[fd_count].events = POLLOUT;
	c->other->idx = fd_count;
	cons[fd_count++] = c->other;
	return 1;
}
