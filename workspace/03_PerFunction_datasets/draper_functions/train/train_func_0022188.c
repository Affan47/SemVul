browse_host_dl_receive(
	struct browse_ctx *bc, gnet_host_t *host, wrap_io_t *wio,
	const char *vendor, uint32 flags)
{
	g_assert(bc != NULL);

	if (bc->closed)
		return FALSE;

	gnet_host_copy(&bc->host, host);
	bc->vendor = atom_str_get(vendor);


	if (bc->rx != NULL) {
		rx_free(bc->rx);
		bc->rx = NULL;
	}

	{
		struct rx_link_args args;

		args.cb = &browse_rx_link_cb;
		args.bws = bsched_in_select_by_addr(gnet_host_get_addr(&bc->host));
		args.wio = wio;

		bc->rx = rx_make(bc, &bc->host, rx_link_get_ops(), &args);
	}

	if (flags & BH_DL_CHUNKED) {
		struct rx_chunk_args args;

		args.cb = &browse_rx_chunk_cb;

		bc->rx = rx_make_above(bc->rx, rx_chunk_get_ops(), &args);
	}

	if (flags & BH_DL_INFLATE) {
		struct rx_inflate_args args;

		args.cb = &browse_rx_inflate_cb;

		bc->rx = rx_make_above(bc->rx, rx_inflate_get_ops(), &args);
	}

	rx_set_data_ind(bc->rx, browse_data_ind);
	rx_enable(bc->rx);

	return TRUE;
}
