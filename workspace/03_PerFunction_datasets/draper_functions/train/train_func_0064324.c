handler_select_check(void *_h, int fd, void *_s)
{
	handler *h = (handler*)_h;
	session *s = (session*)_s;

	if (s->busy != 0)
		return 1;

	if (!s->disconnected)
	{
		char buf;
		int rlen = recv(s->fd, &buf, 1, MSG_PEEK);

		if (rlen == 0)
			s->disconnected = 1;

		if ((rlen < 0) && (errno != EAGAIN) && (errno != EWOULDBLOCK))
			s->disconnected = 1;

		if (s->disconnected)
		{
			sl_int_add(h->badfds, fd, s);
			return 1;
		}
	}

	if (!FD_ISSET(fd, &h->rfds))
		return 1;

	s->busy = 1;
	tpool_start(s->h->tp, &select_run, s);
	return 1;
}
