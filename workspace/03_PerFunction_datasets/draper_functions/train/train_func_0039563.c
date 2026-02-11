realtime_ldap_status(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	char status[256], credentials[100] = "";
	int ctimesec = time(NULL) - connect_time;

	switch (cmd) {
	case CLI_INIT:
		e->command = "realtime show ldap status";
		e->usage =
			"Usage: realtime show ldap status\n"
			"	       Shows connection information for the LDAP RealTime driver\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (!ldapConn)
		return CLI_FAILURE;

	if (!ast_strlen_zero(url))
		snprintf(status, sizeof(status), "Connected to '%s', baseDN %s", url, base_distinguished_name);

	if (!ast_strlen_zero(user))
		snprintf(credentials, sizeof(credentials), " with username %s", user);

	if (ctimesec > 31536000) {
		ast_cli(a->fd, "%s%s for %d years, %d days, %d hours, %d minutes, %d seconds.\n",
				status, credentials, ctimesec / 31536000,
				(ctimesec % 31536000) / 86400, (ctimesec % 86400) / 3600,
				(ctimesec % 3600) / 60, ctimesec % 60);
	} else if (ctimesec > 86400) {
		ast_cli(a->fd, "%s%s for %d days, %d hours, %d minutes, %d seconds.\n",
				status, credentials, ctimesec / 86400, (ctimesec % 86400) / 3600,
				(ctimesec % 3600) / 60, ctimesec % 60);
	} else if (ctimesec > 3600) {
		ast_cli(a->fd, "%s%s for %d hours, %d minutes, %d seconds.\n",
				status, credentials, ctimesec / 3600, (ctimesec % 3600) / 60,
				ctimesec % 60);
	} else if (ctimesec > 60) {
		ast_cli(a->fd, "%s%s for %d minutes, %d seconds.\n", status, credentials,
					ctimesec / 60, ctimesec % 60);
	} else {
		ast_cli(a->fd, "%s%s for %d seconds.\n", status, credentials, ctimesec);
	}

	return CLI_SUCCESS;
}
