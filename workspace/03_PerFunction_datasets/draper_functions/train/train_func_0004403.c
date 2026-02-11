ay_irc_read_config(eb_account *ea, LList *config)
{
	ay_irc_account *eia = g_new0(ay_irc_account, 1);
	char *temp;

	ea->protocol_account_data = eia;


	if ((temp = strrchr(ea->handle, '@')))
		strncpy(eia->server, temp + 1, sizeof(eia->server));

	eia->idle = 0;
	eia->status = IRC_OFFLINE;

	if (ea->ela) {
		irc_local_account *ila = ea->ela->protocol_local_account_data;

		if (!strcmp(ila->ia->connect_address, eia->server))
			ila->friends = l_list_append(ila->friends, ea);
	}
	return ea;
}
