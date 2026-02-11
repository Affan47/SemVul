qos_lg_event_update(request_rec *r, apr_time_t *t) {
  qos_srv_config *sconf = (qos_srv_config*)ap_get_module_config(r->server->module_config,
                                                                &qos_module);
  qs_actable_t *act = sconf->act;
  if(act->has_events && (apr_table_get(r->notes, QS_R012_ALREADY_BLOCKED) == NULL)) {
    apr_time_t now = apr_time_sec(r->request_time);
    qs_acentry_t *e = act->entry;
    *t = now;
    if(e) {
      apr_global_mutex_lock(act->lock);
      while(e) {
        if(e->event) {
          if(((e->event[0] != '!') && apr_table_get(r->subprocess_env, e->event)) ||
             ((e->event[0] == '!') && !apr_table_get(r->subprocess_env, &e->event[1]))) {
            e->req++;
            e->bytes = e->bytes + r->bytes_sent;
            if(now > (e->interval + QS_BW_SAMPLING_RATE)) {
              if(e->req_per_sec_limit) {

                e->req_per_sec = e->req / (now - e->interval);
                e->req = 0;
                e->interval = now;
                qos_cal_req_sec(r, e);
              } else if(e->kbytes_per_sec_limit) {

                e->kbytes_per_sec = e->bytes / (now - e->interval) / 1024;
                e->bytes = 0;
                e->interval = now;
                qos_cal_bytes_sec(r, e);
              }
            }
          }
        }
        e = e->next;
      }
      apr_global_mutex_unlock(act->lock);
    }
  }
}
