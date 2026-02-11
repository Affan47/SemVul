add_unknown_with_name(eb_account *ea, char *name)
{
	struct contact *con = add_new_contact(_("Unknown"),
		(name && strlen(name)) ? name : ea->handle, ea->service_id);

	con->accounts = l_list_prepend(con->accounts, ea);
	ea->account_contact = con;
	ea->icon_handler = ea->status_handler = -1;
	if (find_suitable_local_account_for_remote(ea, NULL))
		RUN_SERVICE(ea)->add_user(ea);
	else {
		contact_mgmt_queue_add(ea, MGMT_ADD,
			ea->account_contact->group->name);
	}
	write_contact_list();
}
