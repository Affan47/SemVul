qos_error_response(request_rec *r, const char *error_page) {
  if(r->subprocess_env) {
    const char *v = apr_table_get(r->subprocess_env, "QS_ErrorPage");
    if(v) {
      error_page = v;
    }
  }
  if(error_page) {

    const char *error_notes;
    r->status = m_retcode;
    r->connection->keepalive = AP_CONN_CLOSE;
    r->no_local_copy = 1;
    apr_table_setn(r->subprocess_env, "REQUEST_METHOD", r->method);
    if ((error_notes = apr_table_get(r->notes,
                                     "error-notes")) != NULL) {
      apr_table_setn(r->subprocess_env, "ERROR_NOTES", error_notes);
    }

    if(strncasecmp(error_page, "http", 4) == 0) {
      apr_table_set(r->headers_out, "Location", error_page);
      return HTTP_MOVED_TEMPORARILY;
    } else {
      r->method = apr_pstrdup(r->pool, "GET");
      r->method_number = M_GET;
      ap_internal_redirect(error_page, r);
      return DONE;
    }
  }
  return DECLINED;
}
