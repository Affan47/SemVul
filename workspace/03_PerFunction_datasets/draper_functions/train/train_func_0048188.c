dbi_result_get_float(dbi_result Result, const char *fieldname) {
  float my_ERROR = 0.0;
  dbi_error_flag errflag = DBI_ERROR_NONE;
  unsigned int fieldidx;

  _reset_conn_error(RESULT->conn);

  fieldidx = _find_field(RESULT, fieldname, &errflag);
  if (errflag != DBI_ERROR_NONE) {
    dbi_conn_t *conn = RESULT->conn;
    _error_handler(conn, DBI_ERROR_BADNAME);
    return my_ERROR;
  }
  return dbi_result_get_float_idx(Result, fieldidx+1);
}
