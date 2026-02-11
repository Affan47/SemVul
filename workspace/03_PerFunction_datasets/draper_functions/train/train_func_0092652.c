ay_irc_del_user(eb_account *account)
{

	ay_irc_account *eia = (ay_irc_account *)account->protocol_account_data;
	eb_local_account *ela = account->ela;

	if (!ela) {
		eb_debug(DBG_MOD, "ela == NULL!\n");
		return;
	}

	if (ela->service_id == SERVICE_INFO.protocol_id) {
		irc_local_account *ila =
			(irc_local_account *)ela->protocol_local_account_data;
		if (eia && eia->server
			&& !strcmp(ila->ia->connect_address, eia->server))
			ila->friends = l_list_remove(ila->friends, account);
	}
}
