net_login(nut_ctype_t *client, int numarg, const char **arg)
{
	upstype_t	*ups;

	if (numarg != 1) {
		send_err(client, NUT_ERR_INVALID_ARGUMENT);
		return;
	}

	if (client->loginups != NULL) {
		upslogx(LOG_INFO, "Client %s@%s tried to login twice", client->username, client->addr);
		send_err(client, NUT_ERR_ALREADY_LOGGED_IN);
		return;
	}


	ups = get_ups_ptr(arg[0]);

	if (!ups) {
		send_err(client, NUT_ERR_UNKNOWN_UPS);
		return;
	}


	if (!user_checkaction(client->username, client->password, "LOGIN")) {
		send_err(client, NUT_ERR_ACCESS_DENIED);
		return;
	}

	ups->numlogins++;
	client->loginups = xstrdup(ups->name);

	upslogx(LOG_INFO, "User %s@%s logged into UPS [%s]%s", client->username, client->addr,
		client->loginups, client->ssl ? " (SSL)" : "");
	sendback(client, "OK\n");
}
