reader_readcb(struct bufferevent *bev, void *ctx)
{
	TT_BLATHER(("Read invoked on %d.", (int)bufferevent_getfd(bev)));
	n_reads_invoked++;
}
