get_content_model(void)
{
	GtkListStore	*store;
	gsize		i;

	store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
	for(i = 0; i < sizeof content_info / sizeof *content_info; i++)
	{
		GtkTreeIter	iter;

		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, 0, _(content_info[i].name_full), 1, content_info[i].id, -1);
	}
	return GTK_TREE_MODEL(store);
}
