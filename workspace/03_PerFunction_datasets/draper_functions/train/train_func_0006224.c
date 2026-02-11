buffers_should_flush(const struct download *d)
{
	const struct dl_buffers *b;

	download_check(d);
	g_assert(d->buffers);

	b = d->buffers;


	return b->held >= b->amount || slist_length(b->list) >= MAX_IOV_COUNT;
}
