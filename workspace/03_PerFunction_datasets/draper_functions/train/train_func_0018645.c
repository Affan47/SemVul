gpk_package_entry_completion_model_new (void)
{
	GPtrArray *list;
	guint i;
	PkPackage *item;
	GHashTable *hash;
	gpointer data;
	GtkListStore *store;
	GtkTreeIter iter;
	gchar **split;

	store = gtk_list_store_new (1, G_TYPE_STRING);
	hash = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
	list = gpk_package_entry_completion_get_names_from_file (PK_SYSTEM_PACKAGE_LIST_FILENAME);
	if (list == NULL) {
		g_warning ("no package list, try refreshing");
		return NULL;
	}

	g_debug ("loading %i autocomplete items", list->len);
	for (i=0; i<list->len; i++) {
		item = g_ptr_array_index (list, i);
		if (item == NULL || pk_package_get_id (item) == NULL) {
			g_warning ("item invalid!");
			break;
		}

		split = pk_package_id_split (pk_package_get_id (item));
		data = g_hash_table_lookup (hash, (gpointer) split[PK_PACKAGE_ID_NAME]);
		if (data == NULL) {

			g_hash_table_insert (hash, g_strdup (split[PK_PACKAGE_ID_NAME]), GINT_TO_POINTER (1));
			gtk_list_store_append (store, &iter);
			gtk_list_store_set (store, &iter, 0, split[PK_PACKAGE_ID_NAME], -1);
		}
		g_strfreev (split);
	}
	g_hash_table_unref (hash);
	g_ptr_array_unref (list);

	return GTK_TREE_MODEL (store);
}
