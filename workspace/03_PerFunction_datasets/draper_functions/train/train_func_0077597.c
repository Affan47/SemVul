stringconn_getter(OVECTOR conn) {
  BVECTOR data = (BVECTOR) AT(conn, CO_HANDLE);
  int pos = NUM(AT(conn, CO_INFO));

  if (conn_closed(conn))
    return CONN_RET_ERROR;

  if (NUM(AT(conn, CO_UNGETC)) != -1) {
    int u = NUM(AT(conn, CO_UNGETC));
    ATPUT(conn, CO_UNGETC, MKNUM(-1));
    return u;
  }

  if (pos >= data->_.length) {
    conn_close(conn);
    return CONN_RET_ERROR;
  }

  ATPUT(conn, CO_INFO, MKNUM(pos+1));
  return AT(data, pos);
}
