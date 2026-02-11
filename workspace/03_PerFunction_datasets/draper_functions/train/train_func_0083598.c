qos_logonly_cmd(cmd_parms *cmd, void *dcfg, int flag) {
  qos_srv_config *sconf = (qos_srv_config*)ap_get_module_config(cmd->server->module_config,
                                                                &qos_module);
  const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
  if (err != NULL) {
    return err;
  }
  sconf->log_only = flag;
  return NULL;
}
