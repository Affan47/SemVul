vfp_nop_bytes(struct sess *sp, struct http_conn *htc, ssize_t bytes)
{
	ssize_t l, w;
	struct storage *st;

	while (bytes > 0) {
		st = FetchStorage(sp, 0);
		if (st == NULL)
			return (-1);
		l = st->space - st->len;
		if (l > bytes)
			l = bytes;
		w = HTC_Read(htc, st->ptr + st->len, l);
		if (w <= 0)
			return (w);
		st->len += w;
		sp->obj->len += w;
		bytes -= w;
		if (sp->wrk->do_stream)
			RES_StreamPoll(sp);
	}
	return (1);
}
