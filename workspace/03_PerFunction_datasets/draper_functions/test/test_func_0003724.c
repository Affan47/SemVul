qos_request_check(request_rec *r, qos_srv_config *sconf) {
  if((r->unparsed_uri == NULL) || (r->parsed_uri.path == NULL)) {
    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                  QOS_LOG_PFX(045)"access denied, invalid request line:"
                  " can't parse uri,%s c=%s, id=%s",
                  sconf->log_only ? " ignores log only mode," : "",
                  QS_CONN_REMOTEIP(r->connection) == NULL ? "-" : QS_CONN_REMOTEIP(r->connection),
                  qos_unique_id(r, "045"));
    return HTTP_BAD_REQUEST;
  }
  return APR_SUCCESS;
}
