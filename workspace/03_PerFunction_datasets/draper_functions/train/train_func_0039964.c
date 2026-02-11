HTC_Read(struct http_conn *htc, void *d, size_t len)
{
	size_t l;
	unsigned char *p;
	ssize_t i;

	l = 0;
	p = d;
	CHECK_OBJ_NOTNULL(htc, HTTP_CONN_MAGIC);
	if (htc->pipeline.b) {
		l = Tlen(htc->pipeline);
		if (l > len)
			l = len;
		memcpy(p, htc->pipeline.b, l);
		p += l;
		len -= l;
		htc->pipeline.b += l;
		if (htc->pipeline.b == htc->pipeline.e)
			htc->pipeline.b = htc->pipeline.e = NULL;
	}
	if (len == 0)
		return (l);
	i = read(htc->fd, p, len);
	if (i < 0) {
		htc->error = strerror(errno);
		return (i);
	} else if (i == 0)
		htc->error = "Remote closed connection";
	return (i + l);
}
