group_handle_normal(GKeyFile * key_file, ShellModuleEntry * entry,
		    gchar * group, gchar ** keys, gsize ngroups)
{
    GtkTreeIter parent;
    GtkTreeStore *store = GTK_TREE_STORE(shell->info->model);
    gchar *tmp = g_strdup(group);
    gint i;

    if (ngroups > 1) {
	gtk_tree_store_append(store, &parent, NULL);

	strend(tmp, '#');
	gtk_tree_store_set(store, &parent, INFO_TREE_COL_NAME, tmp, -1);
	g_free(tmp);
    }

    for (i = 0; keys[i]; i++) {
	gchar *key = keys[i];
	gchar *value;
	GtkTreeIter child;

	value = g_key_file_get_value(key_file, group, key, NULL);
	if (entry->fieldfunc && value && g_str_equal(value, "...")) {
	    g_free(value);
	    value = entry->fieldfunc(key);
	}

	if ((key && value) && g_utf8_validate(key, -1, NULL) && g_utf8_validate(value, -1, NULL)) {
	    if (ngroups == 1) {
		gtk_tree_store_append(store, &child, NULL);
	    } else {
		gtk_tree_store_append(store, &child, &parent);
	    }


	    if (strchr(value, '|')) {
		gchar **columns = g_strsplit(value, "|", 0);

		gtk_tree_store_set(store, &child, INFO_TREE_COL_VALUE, columns[0], -1);
		if (columns[1]) {
			gtk_tree_store_set(store, &child, INFO_TREE_COL_EXTRA1, columns[1], -1);
			if (columns[2]) {
				gtk_tree_store_set(store, &child, INFO_TREE_COL_EXTRA2, columns[2], -1);
			}
		}

		g_strfreev(columns);
	    } else {
	    	gtk_tree_store_set(store, &child, INFO_TREE_COL_VALUE, value, -1);
	    }

	    strend(key, '#');

	    if (*key == '$') {
		gchar **tmp;

		tmp = g_strsplit(++key, "$", 0);

		gtk_tree_store_set(store, &child, INFO_TREE_COL_NAME,
				   tmp[1], INFO_TREE_COL_DATA, tmp[0], -1);

		g_strfreev(tmp);
	    } else {
		gtk_tree_store_set(store, &child, INFO_TREE_COL_NAME, key,
				   INFO_TREE_COL_DATA, NULL, -1);
	    }

	    g_hash_table_insert(update_tbl, g_strdup(key),
				gtk_tree_iter_copy(&child));

	}

	g_free(value);
    }
}
