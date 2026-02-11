evtag_unmarshal_timeval(struct evbuffer *evbuf, ev_uint32_t need_tag,
    struct timeval *ptv)
{
	ev_uint32_t tag;
	ev_uint32_t integer;

	evbuffer_drain(_buf, EVBUFFER_LENGTH(_buf));
	if (evtag_unmarshal(evbuf, &tag, _buf) == -1 || tag != need_tag)
		return (-1);

	if (evtag_decode_int(&integer, _buf) == -1)
		return (-1);
	ptv->tv_sec = integer;
	if (evtag_decode_int(&integer, _buf) == -1)
		return (-1);
	ptv->tv_usec = integer;

	return (0);
}
