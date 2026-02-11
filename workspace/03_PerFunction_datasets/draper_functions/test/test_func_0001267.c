add_group_line(grouplist *eg)
{
	GtkTreeIter iter;


	if (eg->list_item || !contact_list)
		return;

	gtk_tree_store_append(contact_list_store, &iter, NULL);

	gtk_tree_store_set(contact_list_store, &iter,
		MAIN_VIEW_LABEL, eg->name,
		MAIN_VIEW_ROW_DATA, eg,
		MAIN_VIEW_ROW_TYPE, TARGET_TYPE_GROUP,
		MAIN_VIEW_HAS_TIP, FALSE, -1);

	eg->list_item = gtk_tree_iter_copy(&iter);

	eg->contacts_online = 0;
	eg->contacts_shown = 0;
}
