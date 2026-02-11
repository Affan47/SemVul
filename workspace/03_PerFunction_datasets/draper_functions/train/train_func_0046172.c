ay_msn_add_user(eb_account *account)
{
	ay_msn_local_account *mlad;
	LList *buds;

	if (!account->ela || !account->ela->connected)
		return;

	mlad = (ay_msn_local_account *)account->ela->
		protocol_local_account_data;

	buds = mlad->ma->buddies;

	while (buds) {
		MsnBuddy *bud = buds->data;
		if (!strcasecmp(bud->passport, account->handle)
			&& bud->list & MSN_BUDDY_ALLOW) {
			eb_debug(DBG_MSN, "Buddy %s Already Exists\n",
				bud->passport);

			bud->ext_data = account;
			account->protocol_account_data = bud;
			return;
		}

		buds = l_list_next(buds);
	}

	msn_buddy_add(mlad->ma, account->handle, account->account_contact->nick,
		account->account_contact->group->name);
}
