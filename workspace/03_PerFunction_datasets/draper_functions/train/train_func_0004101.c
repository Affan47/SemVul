cli_done(struct cli_def *cli)
{
	struct unp *u = cli->users, *n;

	while (cli->commands) cli_unregister_command(cli, cli->commands->command);
	if (cli->banner) free(cli->banner);

	while (u)
	{
		if (u->username) free(u->username);
		if (u->password) free(u->password);
		n = u->next;
		free(u);
		u = n;
	}

	free(cli);
	return CLI_OK;
}
