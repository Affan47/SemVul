cli_process_cmd(struct cli_client_t *cln)
{
	int found;
	int err;

	if (cli_process_help_cmd(cln))
		return 0;

	found = cli_process_regexp_cmd(cln, &err);
	if (found && err != CLI_CMD_OK)
		goto out_found;

	found |= cli_process_simple_cmd(cln, &err);
	if (found)
		goto out_found;

	if (cli_send(cln, MSG_UNKNOWN_CMD))
		return -1;
	else
		return 0;

out_found:
	switch (err) {
	case CLI_CMD_EXIT:
		cln->disconnect(cln);
		return -1;
	case CLI_CMD_FAILED:
		cli_send(cln, MSG_FAILURE_ERROR);
		return 0;
	case CLI_CMD_SYNTAX:
		cli_send(cln, MSG_SYNTAX_ERROR);
		return 0;
	case CLI_CMD_INVAL:
		cli_send(cln, MSG_INVAL_ERROR);
		return 0;
	case CLI_CMD_OK:
		return 0;
	}
	return -1;
}
