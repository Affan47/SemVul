ay_msn_finish_login(const char *password, void *data)
{
	eb_local_account *account = (eb_local_account *)data;
	char buff[1024];
	ay_msn_local_account *mlad =
		(ay_msn_local_account *)account->protocol_local_account_data;

	snprintf(buff, sizeof(buff), _("Logging in to MSN account: %s"),
		account->handle);
	mlad->activity_tag =
		ay_activity_bar_add(buff, ay_msn_cancel_connect, account);

	mlad->ma->password = strdup(password);

	strncpy(msn_host, ay_msn_host, sizeof(msn_host) - 1);
	strncpy(msn_port, ay_msn_port, sizeof(msn_port) - 1);

	if (!mlad->friendlyname[0])
		mlad->ma->friendlyname = strdup(account->alias);
	else
		mlad->ma->friendlyname = strdup(mlad->friendlyname);

	ref_count++;

	msn_login(mlad->ma);
}
