moreinfo_handle_normal(GKeyFile * key_file, gchar * group, gchar ** keys)
{
    GtkTreeIter parent;
    GtkTreeStore *store = GTK_TREE_STORE(shell->moreinfo->model);
    gint i;

    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, INFO_TREE_COL_NAME, group, -1);

    for (i = 0; keys[i]; i++) {
	gchar *key = keys[i];
	GtkTreeIter child;
	gchar *value;

	value = g_key_file_get_value(key_file, group, key, NULL);

	if (g_utf8_validate(key, -1, NULL)
	    && g_utf8_validate(value, -1, NULL)) {
	    strend(key, '#');

	    gtk_tree_store_append(store, &child, &parent);
	    gtk_tree_store_set(store, &child, INFO_TREE_COL_VALUE,
			       value, INFO_TREE_COL_NAME, key, -1);
	}

	g_free(value);
    }
}
