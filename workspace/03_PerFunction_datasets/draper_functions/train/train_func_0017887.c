dbi_conn_quote_string(dbi_conn Conn, char **orig) {
	dbi_conn_t *conn = Conn;
	char *temp = NULL;
	char *newstr = NULL;
	size_t newlen;

	if (!conn) {
	  return 0;
	}

	_reset_conn_error(conn);

	if (!orig || !*orig) {
	  _error_handler(conn, DBI_ERROR_BADPTR);
	  return 0;
	}

	newlen = dbi_conn_quote_string_copy(Conn, *orig, &newstr);
	if (!newlen) {


	  return 0;
	}
	temp = *orig;
	*orig = newstr;
	free(temp);

	return newlen;
}
