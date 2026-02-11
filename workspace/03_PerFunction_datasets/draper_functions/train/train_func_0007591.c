qos_hp_event_filter(request_rec *r, qos_srv_config *sconf) {
  apr_status_t rv = DECLINED;
  qs_req_ctx *rctx = qos_rctx_config_get(r);
  qs_actable_t *act = sconf->act;
  if(act->has_events) {
    qs_acentry_t *e = act->entry;
    if(e) {
      apr_global_mutex_lock(act->lock);
      while(e) {
        if(e->event && (e->limit != -1)) {
          const char *var = apr_table_get(r->subprocess_env, e->event);
          if(var) {
            int match = 1;
            if(e->regex_var) {
              if(ap_regexec(e->regex_var, var, 0, NULL, 0) != 0) {
                match = 0;
              }
            }
            if(match) {
              apr_table_addn(rctx->event_entries, e->url, (char *)e);
              e->counter++;
              if(e->counter > e->limit) {
                rv = m_retcode;
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                              QOS_LOG_PFX(012)"access denied, QS_EventRequestLimit rule: %s(%d),"
                              " concurrent requests=%d,"
                              " c=%s, id=%s",
                              e->url, e->limit, e->counter,
                              QS_CONN_REMOTEIP(r->connection) == NULL ? "-" : QS_CONN_REMOTEIP(r->connection),
                              qos_unique_id(r, "012"));
                apr_table_set(r->notes, QS_R012_ALREADY_BLOCKED, "");
              }
            }
          }
        }
        e = e->next;
      }
      apr_global_mutex_unlock(act->lock);
    }
  }
  if(rv != DECLINED) {
    int rc;
    const char *error_page = sconf->error_page;
    qs_req_ctx *rctx = qos_rctx_config_get(r);
    rctx->evmsg = apr_pstrcat(r->pool, "D;", rctx->evmsg, NULL);
    if(!sconf->log_only) {
      rc = qos_error_response(r, error_page);
      if((rc == DONE) || (rc == HTTP_MOVED_TEMPORARILY)) {
        rv = rc;
      }
    } else {
      return DECLINED;
    }
  }
  return rv;
}
