cli_allow_user(struct cli_def *cli, char *username, char *password)
{
	struct unp *u, *n;
	n = malloc(sizeof(struct unp));
	n->username = strdup(username);
	n->password = strdup(password);
	n->next = NULL;

	if (!cli->users)
		cli->users = n;
	else
	{
		for (u = cli->users; u && u->next; u = u->next);
		if (u) u->next = n;
	}
}
