qos_event_setenvresbody_cmd(cmd_parms *cmd, void *dcfg, const char *pattern,
                                        const char *var) {
  qos_dir_config *dconf = (qos_dir_config*)dcfg;
  if(dconf->response_pattern) {
    return apr_psprintf(cmd->pool, "%s: only one pattern must be configured for a location",
                        cmd->directive->directive);
  }
  dconf->response_pattern = apr_pstrdup(cmd->pool, pattern);
  dconf->response_pattern_var = apr_pstrdup(cmd->pool, var);
  return NULL;
}
