gsearch_create_list_of_templates (void)
{
	GtkListStore * store;
	GtkTreeIter iter;
	gint idx;

	store = gtk_list_store_new (1, G_TYPE_STRING);

	for (idx = 0; GSearchOptionTemplates[idx].type != SEARCH_CONSTRAINT_TYPE_NONE; idx++) {

		if (GSearchOptionTemplates[idx].type == SEARCH_CONSTRAINT_TYPE_SEPARATOR) {
		        gtk_list_store_append (store, &iter);
		        gtk_list_store_set (store, &iter, 0, "separator", -1);
		}
		else {
			gchar * text = remove_mnemonic_character (_(GSearchOptionTemplates[idx].desc));
			gtk_list_store_append (store, &iter);
		        gtk_list_store_set (store, &iter, 0, text, -1);
			g_free (text);
		}
	}
	return GTK_TREE_MODEL (store);
}
