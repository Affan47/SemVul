buddy_login(eb_account *ea)
{

	if (ea->online)
		return;

	ea->account_contact->online++;
	ea->online = TRUE;

	if (iGetLocalPref("do_ignore_unknown")
		&& !strcmp(_("Unknown"), ea->account_contact->group->name))
		return;

	add_account_line(ea);


	ea->pix = iconlogin_pb;


	if (ea->icon_handler != -1)
		eb_timeout_remove(ea->icon_handler);

	ea->icon_handler =
		eb_timeout_add(5000, (GtkFunction) set_account_icon,
		(gpointer) ea);


	if (ea->account_contact->online == 1)
		contact_login(ea->account_contact);

	gtk_tree_store_set(contact_list_store, ea->list_item,
		MAIN_VIEW_ICON, ea->pix, MAIN_VIEW_STATUS, ea->status, -1);
}
