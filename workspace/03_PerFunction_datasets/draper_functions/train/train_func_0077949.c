thex_download_receive(struct thex_download *ctx,
	filesize_t content_length,
	gnet_host_t *host, struct wrap_io *wio, uint32 flags)
{
	g_assert(ctx != NULL);

	gnet_host_copy(&ctx->host, host);


	if (ctx->rx != NULL) {
		rx_free(ctx->rx);
		ctx->rx = NULL;
	}


	if (content_length > MAX_INT_VAL(size_t))
		return FALSE;

	ctx->max_size = content_length ?
		(size_t) content_length : THEX_DOWNLOAD_MAX_SIZE;

	{
		struct rx_link_args args;

		args.cb = &thex_rx_link_cb;
		args.bws = bsched_in_select_by_addr(gnet_host_get_addr(&ctx->host));
		args.wio = wio;

		ctx->rx = rx_make(ctx, &ctx->host, rx_link_get_ops(), &args);
	}

	if (flags & THEX_DOWNLOAD_F_CHUNKED) {
		struct rx_chunk_args args;

		args.cb = &thex_rx_chunk_cb;

		ctx->rx = rx_make_above(ctx->rx, rx_chunk_get_ops(), &args);
	}

	if (flags & THEX_DOWNLOAD_F_INFLATE) {
		struct rx_inflate_args args;

		args.cb = &thex_rx_inflate_cb;

		ctx->rx = rx_make_above(ctx->rx, rx_inflate_get_ops(), &args);
	}

	rx_set_data_ind(ctx->rx, thex_download_data_ind);
	rx_enable(ctx->rx);

	return TRUE;
}
