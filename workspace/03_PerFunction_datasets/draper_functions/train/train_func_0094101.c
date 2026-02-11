dbi_result_get_field_attrib(dbi_result Result, const char *fieldname, unsigned int attribmin, unsigned int attribmax) {
  unsigned int fieldidx = 0;
  dbi_error_flag errflag = DBI_ERROR_NONE;

  if (!RESULT) {
    _error_handler( NULL, DBI_ERROR_BADPTR);
    return DBI_ATTRIBUTE_ERROR;
  }

  _reset_conn_error(RESULT->conn);

  fieldidx = _find_field(RESULT, fieldname, &errflag);
  if (errflag != DBI_ERROR_NONE) {
    _error_handler(RESULT->conn, errflag);
    return DBI_ATTRIBUTE_ERROR;
  }

  return dbi_result_get_field_attrib_idx(Result, fieldidx+1, attribmin, attribmax);
}
