dbi_result_get_double_idx(dbi_result Result, unsigned int fieldidx) {
  double my_ERROR = 0.0;
  fieldidx--;

  _reset_conn_error(RESULT->conn);

  if (fieldidx >= RESULT->numfields) {
    _error_handler(RESULT->conn, DBI_ERROR_BADIDX);
    return my_ERROR;
  }
  if (RESULT->field_types[fieldidx] != DBI_TYPE_DECIMAL) {
    _verbose_handler(RESULT->conn, "%s: field `%s` is not double type\n",
                     __func__, dbi_result_get_field_name(Result, fieldidx+1));
    _error_handler(RESULT->conn, DBI_ERROR_BADTYPE);
    return my_ERROR;
  }

  switch (RESULT->field_attribs[fieldidx] & DBI_DECIMAL_SIZEMASK) {
  case DBI_DECIMAL_SIZE4:
    return RESULT->rows[RESULT->currowidx]->field_values[fieldidx].d_float;
  case DBI_DECIMAL_SIZE8:
    return RESULT->rows[RESULT->currowidx]->field_values[fieldidx].d_double;
  default:
    _error_handler(RESULT->conn, DBI_ERROR_BADTYPE);
    return my_ERROR;
  }
}
