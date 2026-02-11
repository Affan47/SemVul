reload_exec(const char *cmd, char * const *f, int f_cnt, void *cli)
{
	if (f_cnt == 1) {
		conf_reload_ctx = triton_context_self();
		triton_conf_reload(conf_reload_notify);
		triton_context_schedule();
		if (conf_reload_res)
			cli_send(cli, "failed\r\n");
		return CLI_CMD_OK;
	} else
		return CLI_CMD_SYNTAX;
}
