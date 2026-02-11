cmd_exec(const char *cmd, char * const *fields, int fields_cnt, void *client)
{
	if (fields_cnt == 2)
		goto help;

	if (!strcmp(fields[2], "reload")) {
		if (!conf_mac_filter)
			cli_send(client, "error: mac-filter was not specified in the config\r\n");
		else if (mac_filter_load(conf_mac_filter))
			cli_send(client, "error: check logs\r\n");
	} else if (!strcmp(fields[2], "add")) {
		if (fields_cnt != 4)
			goto help;
		mac_filter_add(fields[3], client);
	} else if (!strcmp(fields[2], "del")) {
		if (fields_cnt != 4)
			goto help;
		mac_filter_del(fields[3], client);
	} else if (!strcmp(fields[2], "show")) {
		mac_filter_show(client);
	} else
		goto help;

	return CLI_CMD_OK;
help:
	cmd_help(fields, fields_cnt, client);
	return CLI_CMD_OK;
}
