mod_status_handler(server *srv, connection *con, void *p_d) {
	plugin_data *p = p_d;

	if (con->mode != DIRECT) return HANDLER_GO_ON;

	mod_status_patch_connection(srv, con, p);

	if (!buffer_is_empty(p->conf.status_url) &&
	    buffer_is_equal(p->conf.status_url, con->uri.path)) {
		return mod_status_handle_server_status(srv, con, p_d);
	} else if (!buffer_is_empty(p->conf.config_url) &&
	    buffer_is_equal(p->conf.config_url, con->uri.path)) {
		return mod_status_handle_server_config(srv, con, p_d);
	} else if (!buffer_is_empty(p->conf.statistics_url) &&
	    buffer_is_equal(p->conf.statistics_url, con->uri.path)) {
		return mod_status_handle_server_statistics(srv, con, p_d);
	}

	return HANDLER_GO_ON;
}
