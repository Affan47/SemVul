evtag_unmarshal_timeval(struct evbuffer *evbuf, ev_uint32_t need_tag,
    struct timeval *ptv)
{
	ev_uint32_t tag;
	ev_uint32_t integer;
	int len, offset, offset2;
	int result = -1;

	if ((len = evtag_unmarshal_header(evbuf, &tag)) == -1)
		return (-1);
	if (tag != need_tag)
		goto done;
	if ((offset = decode_int_internal(&integer, evbuf, 0)) == -1)
		goto done;
	ptv->tv_sec = integer;
	if ((offset2 = decode_int_internal(&integer, evbuf, offset)) == -1)
		goto done;
	ptv->tv_usec = integer;
	if (offset + offset2 > len)
		goto done;

	result = 0;
 done:
	evbuffer_drain(evbuf, len);
	return result;
}
