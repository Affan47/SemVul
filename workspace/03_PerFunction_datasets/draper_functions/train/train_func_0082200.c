bufferevent_filter_new(struct bufferevent *underlying,
		       bufferevent_filter_cb input_filter,
		       bufferevent_filter_cb output_filter,
		       int options,
		       void (*free_context)(void *),
		       void *ctx)
{
	struct bufferevent_filtered *bufev_f;
	int tmp_options = options & ~BEV_OPT_THREADSAFE;

	if (!input_filter)
		input_filter = be_null_filter;
	if (!output_filter)
		output_filter = be_null_filter;

	bufev_f = mm_calloc(1, sizeof(struct bufferevent_filtered));
	if (!bufev_f)
		return NULL;

	if (bufferevent_init_common(&bufev_f->bev, underlying->ev_base,
				    &bufferevent_ops_filter, tmp_options) < 0) {
		mm_free(bufev_f);
		return NULL;
	}
	if (options & BEV_OPT_THREADSAFE) {
		bufferevent_enable_locking(downcast(bufev_f), NULL);
	}

	bufev_f->underlying = underlying;
	bufev_f->process_in = input_filter;
	bufev_f->process_out = output_filter;
	bufev_f->free_context = free_context;
	bufev_f->context = ctx;

	bufferevent_setcb(bufev_f->underlying,
            be_filter_readcb, be_filter_writecb, be_filter_eventcb, bufev_f);

	bufev_f->outbuf_cb = evbuffer_add_cb(downcast(bufev_f)->output,
	   bufferevent_filtered_outbuf_cb, bufev_f);

	_bufferevent_init_generic_timeout_cbs(downcast(bufev_f));
	bufferevent_incref(underlying);

	return downcast(bufev_f);
}
