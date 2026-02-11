dbi_result_get_string_copy(dbi_result Result, const char *fieldname) {
  char *my_ERROR = "ERROR";
  unsigned int fieldidx;
  dbi_error_flag errflag = DBI_ERROR_NONE;

  _reset_conn_error(RESULT->conn);

  fieldidx = _find_field(RESULT, fieldname, &errflag);
  if (errflag != DBI_ERROR_NONE) {
    dbi_conn_t *conn = RESULT->conn;
    _error_handler(conn, DBI_ERROR_BADNAME);
    return strdup(my_ERROR);
  }
  return dbi_result_get_string_copy_idx(Result, fieldidx+1);
}
