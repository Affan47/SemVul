qos_count_connections(qos_srv_config *sconf) {
  server_rec *s = sconf->base_server;
  qos_srv_config *bsconf = (qos_srv_config*)ap_get_module_config(s->module_config, &qos_module);
  if(QS_COUNT_CONNECTIONS(bsconf)) {
    return 1;
  }
  s = s->next;
  while(s) {
    qos_srv_config *sc = (qos_srv_config*)ap_get_module_config(s->module_config, &qos_module);
    if(QS_COUNT_CONNECTIONS(sc)) {
      return 1;
    }
    s = s->next;
  }
  return 0;
}
