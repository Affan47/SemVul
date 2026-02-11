msn_got_usr_response(MsnConnection *mc, void *data)
{
	if (mc->current_message->command == MSN_COMMAND_XFR) {

		char *port_offset = NULL;
		MsnAccount *ma = mc->account;

		ma->ns_connection = msn_connection_new();

		ma->ns_connection->host = strdup(mc->current_message->argv[3]);
		port_offset = strchr(ma->ns_connection->host, ':');

		if (!port_offset) {
			msn_connection_free(ma->ns_connection);
			ma->ns_connection = NULL;

			ext_msn_login_response(mc->account,
				MSN_LOGIN_FAIL_OTHER);
			msn_connection_free(mc);

			return;
		}

		*port_offset = '\0';

		ma->ns_connection->port = atoi(++port_offset);

		ma->ns_connection->type = MSN_CONNECTION_NS;
		ma->ns_connection->account = ma;


		mc->account = NULL;

		msn_connection_connect(ma->ns_connection, msn_login_connected);
	} else {

		mc->account->policy = strdup(mc->current_message->argv[4]);
		mc->account->nonce =
			(unsigned char *)strdup(mc->current_message->argv[5]);
		mc->account->nonce_len = strlen((char *)mc->account->nonce);

		msn_sso_start(mc->account);
	}
}
