dbi_result_get_conn(dbi_result Result) {

  if (!RESULT) {
    _error_handler( NULL, DBI_ERROR_BADPTR);
    return NULL;
  }

  return RESULT->conn;
}
