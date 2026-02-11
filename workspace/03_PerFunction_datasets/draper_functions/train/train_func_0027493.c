dbi_conn_get_option_list(dbi_conn Conn, const char *current) {
	dbi_conn_t *conn = Conn;
	dbi_option_t *option;

	if (!conn) {
	  return NULL;
	}

	_reset_conn_error(conn);

	if (!conn->options) {
	  _error_handler(conn, DBI_ERROR_BADPTR);
	  return NULL;
	}
	option = conn->options;

	if (!current) {
		return option->key;
	}
	else {
		while (option && strcasecmp(current, option->key)) {
			option = option->next;
		}


		return (option && option->next) ? option->next->key : NULL;
	}
}
