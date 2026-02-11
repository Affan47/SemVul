hide_contact(struct contact *ec)
{
	LList *l;

	if (ec->icon_handler == -1)
		return FALSE;

	ec->icon_handler = -1;

	if (status_show == 2)
		remove_contact_line(ec);
	else {
		for (l = ec->accounts; l; l = l->next) {
			eb_account *account = l->data;
			buddy_update_icon(account);
		}
		contact_update_status(ec);
	}

	return FALSE;
}
