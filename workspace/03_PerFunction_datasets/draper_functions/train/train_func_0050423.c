qos_req_rate_tm_cmd(cmd_parms *cmd, void *dcfg, const char *arg1) {
  qos_srv_config *sconf = (qos_srv_config*)ap_get_module_config(cmd->server->module_config,
                                                                &qos_module);
  const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
  if (err != NULL) {
    return err;
  }
  sconf->qs_req_rate_tm= atoi(arg1);
  if(sconf->qs_req_rate_tm <= 0) {
    return apr_psprintf(cmd->pool, "%s: must be numeric value between >0",
                        cmd->directive->directive);
  }
  return NULL;
}
