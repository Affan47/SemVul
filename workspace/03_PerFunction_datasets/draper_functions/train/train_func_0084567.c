qos_per_dir_event_rules(request_rec *r, qos_dir_config *dconf) {
  apr_table_entry_t *entry = (apr_table_entry_t *)apr_table_elts(dconf->rfilter_table)->elts;
  int i;
  for(i = 0; i < apr_table_elts(dconf->rfilter_table)->nelts; i++) {
    if(entry[i].key[0] == '+') {
      int deny_rule = 0;
      int ex = -1;
      qos_rfilter_t *rfilter = (qos_rfilter_t *)entry[i].val;
      if(rfilter->type == QS_DENY_EVENT) {
        deny_rule = 1;
        if(rfilter->text[0] == '!') {
          if(apr_table_get(r->subprocess_env, &rfilter->text[1]) == NULL) {
            ex = 0;
          }
        } else {
          if(apr_table_get(r->subprocess_env, rfilter->text) != NULL) {
            ex = 0;
          }
        }
      }
      if(deny_rule && (ex == 0)) {
        int severity = rfilter->action == QS_DENY ? APLOG_ERR : APLOG_WARNING;
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|severity, 0, r,
                      QOS_LOG_PFX(040)"access denied, %s rule id: %s (%s),"
                      " action=%s, c=%s, id=%s",
                      qos_rfilter_type2text(r->pool, rfilter->type),
                      rfilter->id,
                      rfilter->text, rfilter->action == QS_DENY ? "deny" : "log only",
                      QS_CONN_REMOTEIP(r->connection) == NULL ? "-" : QS_CONN_REMOTEIP(r->connection),
                      qos_unique_id(r, "040"));
        if(rfilter->action == QS_DENY) {
          return HTTP_FORBIDDEN;
        }
      }
    }
  }
  return APR_SUCCESS;
}
