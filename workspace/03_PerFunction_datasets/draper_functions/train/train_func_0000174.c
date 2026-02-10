add_account_verbose(char *contact, eb_account *ea, int verbosity)
{
	struct relocate_account_data *rad;
	struct contact *c = find_contact_by_nick(contact);
	eb_account *account;
	if (ea->ela)
		account = find_account_with_ela(ea->handle, ea->ela);
	else
		account = find_account_by_handle(ea->handle, ea->service_id);

	if (account) {
		if (!strcasecmp(account->account_contact->group->name,
				_("Unknown"))
			|| strstr(account->account_contact->group->name,
				"__Ayttm_Dummy_Group__")
			== account->account_contact->group->name) {
			move_account(c, account);
		} else {
			char buff[2048];
			snprintf(buff, sizeof(buff),
				_("The account \"%s\" already exists on your\n"
					"contact list at the following location\n"
					"\tGroup: %s\n"
					"\tContact: %s\n"
					"\nShould I move it?"),
				account->handle,
				account->account_contact->group->name,
				account->account_contact->nick);


			if (verbosity) {
				rad = calloc(1,
					sizeof(struct relocate_account_data));
				rad->account = account;
				rad->contact = c;
				eb_do_dialog(buff, _("Error: account exists"),
					move_account_yn, rad);
			} else if (c && l_list_empty(c->accounts))
				remove_contact(c);
		}
		return;
	}
	if (!find_suitable_local_account_for_remote(ea, NULL)) {
		contact_mgmt_queue_add(ea, MGMT_ADD,
			c ? c->group->name : _("Unknown"));
	}
	if (c) {
		c->accounts =
			l_list_insert_sorted(c->accounts, ea, account_cmp);
		ea->account_contact = c;
		RUN_SERVICE(ea)->add_user(ea);

		if (!strcmp(c->group->name, _("Ignore")) &&
			RUN_SERVICE(ea)->ignore_user)
			RUN_SERVICE(ea)->ignore_user(ea);
	} else
		add_unknown_with_name(ea, contact);

	update_contact_list();
	write_contact_list();
}
