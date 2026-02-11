_dbd_internal_error_handler(dbi_conn_t *conn, const char *errmsg, const int err_no) {
  int my_errno = DBI_ERROR_NONE;
  int errstatus;
  char *my_errmsg = NULL;

  if (conn->error_message) {
    free(conn->error_message);
  }

  if (err_no == DBI_ERROR_DBD) {

    errstatus = conn->driver->functions->geterror(conn, &my_errno, &my_errmsg);

    if (errstatus == -1) {

      return;
    }
    conn->error_flag = my_errno;
    conn->error_number = my_errno;
    conn->error_message = my_errmsg ? my_errmsg : NULL;

    if (conn->error_handler != NULL) {
      conn->error_handler((dbi_conn)conn, conn->error_handler_argument);
    }
  }
  else if (errmsg) {
    conn->error_flag = err_no;
    conn->error_number = err_no;
    conn->error_message = strdup(errmsg);

    if (conn->error_handler != NULL) {
      conn->error_handler((dbi_conn)conn, conn->error_handler_argument);
    }
  }
  else {

    _error_handler(conn, err_no);
  }

}
