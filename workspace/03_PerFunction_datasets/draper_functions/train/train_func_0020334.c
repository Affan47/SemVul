dbi_conn_quote_binary_copy(dbi_conn Conn, const unsigned char *orig, size_t from_length, unsigned char **ptr_dest) {
  unsigned char *temp = NULL;
  size_t newlen;
  dbi_conn_t *conn = Conn;

  if (!conn) {
    return 0;
  }

  _reset_conn_error(conn);

  if (!orig || !ptr_dest) {
    _error_handler(conn, DBI_ERROR_BADPTR);
    return 0;
  }

  newlen = conn->driver->functions->quote_binary(conn, orig, from_length, &temp);
  if (!newlen) {
    _error_handler(conn, DBI_ERROR_NOMEM);
    return 0;
  }

  *ptr_dest = temp;

  return newlen;
}
