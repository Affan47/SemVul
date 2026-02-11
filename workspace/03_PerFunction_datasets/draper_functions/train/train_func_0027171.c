sig_print_starting(void)
{
	GSList *tmp, *next;

	if (printing_joins)
		return;

	for (tmp = joinservers; tmp != NULL; tmp = next) {
		NETJOIN_SERVER_REC *server = tmp->data;

		next = tmp->next;
		if (server->netjoins != NULL)
			print_netjoins(server);
	}
}
