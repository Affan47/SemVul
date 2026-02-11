dbi_conn_queryf(dbi_conn Conn, const char *formatstr, ...) {
	dbi_conn_t *conn = Conn;
	char *statement;
	dbi_result_t *result;
	va_list ap;

	if (!conn || !(conn->connection)) return NULL;

	_reset_conn_error(conn);

	va_start(ap, formatstr);
	vasprintf(&statement, formatstr, ap);
	va_end(ap);

	_logquery(conn, "[queryf] %s\n", statement);
	result = conn->driver->functions->query(conn, statement);

	if (result == NULL) {
		_error_handler(conn, DBI_ERROR_DBD);
	}
	free(statement);

	return (dbi_result)result;
}
