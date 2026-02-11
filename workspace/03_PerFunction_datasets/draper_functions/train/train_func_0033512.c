group_changed(GtkEditable *editable, gpointer user_data)
{
	GList *list = llist_to_glist(get_contacts(COMBO_TEXT(group)), 1);
	GList *gwalker;
	for (gwalker = list; gwalker; gwalker = g_list_next(gwalker))
		gtk_combo_box_append_text(GTK_COMBO_BOX(nick), gwalker->data);
	g_list_free(list);

	if (account->account_contact)
		gtk_entry_set_text(GTK_ENTRY(GTK_BIN(nick)->child),
			account->account_contact->nick);
	else
		gtk_entry_set_text(GTK_ENTRY(GTK_BIN(nick)->child),
			account->handle);
}
