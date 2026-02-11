set_account_icon(eb_account *ea)
{

	if (ea->icon_handler == -1)
		return FALSE;
	ea->icon_handler = -1;


	if (ea->account_contact->online == 1)
		do_trigger_online(ea->account_contact);

	buddy_update_icon(ea);
	return FALSE;
}
