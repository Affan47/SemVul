evtag_consume(struct evbuffer *evbuf)
{
	int len;
	if ((len = evtag_unmarshal_header(evbuf, NULL)) == -1)
		return (-1);
	evbuffer_drain(evbuf, len);

	return (0);
}
