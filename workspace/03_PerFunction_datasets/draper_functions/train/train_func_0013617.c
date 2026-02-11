set_buf_size(cmd_parms *cmd, void *mconfig, const char *value)
{
  int size;
  char *ptr;
  dacs_server_config *sc_rec;

  sc_rec = ap_get_module_config(cmd->server->module_config,
								&auth_dacs_module);

  if (value == NULL)
	return("integer value expected for buffer size");
  size = strtol(value, &ptr, 10);
  if (*ptr != '\0' || size < 0)
	return("illegal integer value for buffer size");

  if (strcasecmp(cmd->cmd->name, "SetDACSAuthEnvBuffer") == 0) {
	if (size < DACS_MINIMUM_ENV_BUF_SIZE || size > DACS_MAXIMUM_ENV_BUF_SIZE)
	  return("Value out-of-range for SetDACSAuthEnvBuffer size");
	sc_rec->env_buf_size = size;
	if (debug_enabled(sc_rec))
	  ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
				   "set env_buf_size=%d%s for server %s:%u", size,
				   config_src(cmd),
				   cmd->server->server_hostname,
				   (unsigned int) cmd->server->port);
  }
  else if (strcasecmp(cmd->cmd->name, "SetDACSAuthPostBuffer") == 0) {
	if (size != 0
		&& (size < DACS_MINIMUM_POST_BUF_SIZE
			|| size > DACS_MAXIMUM_POST_BUF_SIZE))
	  return("Value out-of-range for SetDACSAuthPostBuffer size");
	sc_rec->post_buf_size = size;
	if (debug_enabled(sc_rec))
	  ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
				   "set post_buf_size=%d%s for server %s:%u", size,
				   config_src(cmd), cmd->server->server_hostname,
				   (unsigned int) cmd->server->port);
  }
  else
	return("command name botch - internal error!");

  return(NULL);
}
