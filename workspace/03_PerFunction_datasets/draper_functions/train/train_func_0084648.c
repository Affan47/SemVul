session_read(session *s, void *buf, size_t len)
{
	if (!s || !buf || !len)
		return 0;

	if (s->disconnected)
		return 0;

	int rlen;

#if USE_SSL
	if (s->is_ssl)
	{
		rlen = SSL_read((SSL*)s->ssl, s->srcbuf, BUFLEN-1);
	}
	else
#endif
	if (s->tcp)
	{
		rlen = recv(s->fd, (char*)buf, len, 0);
	}
	else if (s->ipv4)
	{
		socklen_t alen = sizeof(struct sockaddr_in);
		rlen = recvfrom(s->fd, (char*)buf, len, 0, (struct sockaddr*)&s->addr4, &alen);
	}
	else
	{
		socklen_t alen = sizeof(struct sockaddr_in6);
		rlen = recvfrom(s->fd, (char*)buf, len, 0, (struct sockaddr*)&s->addr6, &alen);
	}

	if ((rlen < 0) &&
		((errno == EAGAIN) || (errno == EWOULDBLOCK) || (errno == EINTR)))
		return 0;

	if (rlen <= 0)
	{
		if (s->tcp)
			s->disconnected = 1;

		return 0;
	}

	return rlen > 0;
}
