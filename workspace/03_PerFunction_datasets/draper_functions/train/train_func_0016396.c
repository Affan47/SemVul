evtag_consume(struct evbuffer *evbuf)
{
	ev_uint32_t len;
	if (decode_tag_internal(NULL, evbuf, 1 ) == -1)
		return (-1);
	if (evtag_decode_int(&len, evbuf) == -1)
		return (-1);
	evbuffer_drain(evbuf, len);

	return (0);
}
