_get_option(dbi_conn Conn, const char *key, int aggressive) {
	dbi_conn_t *conn = Conn;
	dbi_option_t *option;

	if (!conn) {
		return NULL;
	}

	_reset_conn_error(conn);

	option = conn->options;
	while (option && strcasecmp(key, option->key)) {
		option = option->next;
	}

	if (option) {
		return option->string_value;
	}
	else {
		if (aggressive) _error_handler(conn, DBI_ERROR_BADNAME);
		return NULL;
	}
}
