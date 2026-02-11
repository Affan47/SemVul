fcgi_reconnect(server *srv, handler_ctx *hctx) {
	plugin_data *p    = hctx->plugin_data;


	if (hctx->fd != -1) {
		fdevent_event_del(srv->ev, &(hctx->fde_ndx), hctx->fd);
		fdevent_unregister(srv->ev, hctx->fd);
		close(hctx->fd);
		srv->cur_fds--;
		hctx->fd = -1;
	}

	fcgi_set_state(srv, hctx, FCGI_STATE_INIT);

	hctx->request_id = 0;
	hctx->reconnects++;

	if (p->conf.debug > 2) {
		if (hctx->proc) {
			log_error_write(srv, __FILE__, __LINE__, "sdb",
					"release proc for reconnect:",
					hctx->proc->pid, hctx->proc->connection_name);
		} else {
			log_error_write(srv, __FILE__, __LINE__, "sb",
					"release proc for reconnect:",
					hctx->host->unixsocket);
		}
	}

	if (hctx->proc && hctx->got_proc) {
		fcgi_proc_load_dec(srv, hctx);
	}


	fcgi_host_reset(srv, hctx);

	return 0;
}
