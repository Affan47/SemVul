buffers_reset_reading(struct download *d)
{
	struct dl_buffers *b;

	download_check(d);
	g_assert(d->buffers != NULL);
	g_assert(DOWNLOAD_IS_ACTIVE(d));
	g_assert(d->buffers->held == 0);

	b = d->buffers;
	pmsg_slist_discard_all(b->list);
	b->mode = DL_BUF_READING;
}
