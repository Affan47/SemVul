dbi_conn_clear_options(dbi_conn Conn) {
	dbi_conn_t *conn = Conn;
	dbi_option_t *cur;
	dbi_option_t *next;

	if (!conn) return;
	cur = conn->options;

	while (cur) {
		next = cur->next;
		free(cur->key);
		free(cur->string_value);
		free(cur);
		cur = next;
	}

	conn->options = NULL;
}
