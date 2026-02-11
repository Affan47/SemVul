tls_new(int type, int flags)
{
	tls_state *tls = xmalloc(sizeof(tls_state));

	debug("Initializing connection context");

	tls->data = NULL;
	tls->id = NULL;
	tls->addr = NULL;
	tls->peer = NULL;
	tls->init_watcher.data = tls;
	tls->read_watcher.data = tls;
	tls->write_watcher.data = tls;
	tls->shutdown_watcher.data = tls;
	tls->timeout_watcher.data = tls;
	tls->timeout = 0.0;
	tls->last_activity = ev_now(EV_DEFAULT_UC);
	tls->input_buffer = buffer_new();
	tls->output_buffer = buffer_new();
	tls->input = NULL;
	tls->output = NULL;
	tls->input_size = 0;
	tls->input_offset = 0;
	tls->output_size = 0;
	tls->output_offset = 0;
	tls->connect_handler = NULL;
	tls->read_handler = NULL;
	tls->drain_handler = NULL;
	tls->error_handler = NULL;
	tls->timeout_handler = default_timeout_handler;
	tls->line_too_long_handler = default_line_too_long_handler;
	tls->free_output = free;
	tls->ssl = NULL;
	tls->bio = NULL;
	tls->fd = -1;
	tls->read_mode = 0;

	if (flags & TLS_AUTO_DIE) {
		warning_f = die;
		error_f = die;
	} else {
		warning_f = warning;
		error_f = error;
	}

	ev_init(&tls->init_watcher,
	    type == TLS_CLIENT ? connect_cb : accept_ssl_cb);
	ev_init(&tls->read_watcher, read_cb);
	ev_init(&tls->write_watcher, write_cb);
	ev_init(&tls->shutdown_watcher, shutdown_cb);
	ev_init(&tls->timeout_watcher, timeout_cb);


	ev_set_priority(&tls->timeout_watcher, -1);

	return tls;
}
