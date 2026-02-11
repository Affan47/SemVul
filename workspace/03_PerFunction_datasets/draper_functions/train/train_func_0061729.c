synch_user_menu (GtkComboBox *combo_box, NautilusFile *file)
{
	GList *users;
	GList *node;
	GtkTreeModel *model;
	GtkListStore *store;
	GtkTreeIter iter;
	char *user_name;
	char *owner_name;
	int user_index;
	int owner_index;
	char **name_array;
	char *combo_text;

	g_assert (GTK_IS_COMBO_BOX (combo_box));
	g_assert (NAUTILUS_IS_FILE (file));

	if (nautilus_file_is_gone (file)) {
		return;
	}

	users = nautilus_get_user_names ();

	model = gtk_combo_box_get_model (combo_box);
	store = GTK_LIST_STORE (model);
	g_assert (GTK_IS_LIST_STORE (model));

	if (!tree_model_entries_equal (model, 1, users)) {


		gtk_list_store_clear (store);

		for (node = users, user_index = 0; node != NULL; node = node->next, ++user_index) {
			user_name = (char *)node->data;

			name_array = g_strsplit (user_name, "\n", 2);
			if (name_array[1] != NULL) {
				combo_text = g_strdup_printf ("%s - %s", name_array[0], name_array[1]);
			} else {
				combo_text = g_strdup (name_array[0]);
			}

			gtk_list_store_append (store, &iter);
			gtk_list_store_set (store, &iter,
					    0, combo_text,
					    1, user_name,
					    -1);

			g_strfreev (name_array);
			g_free (combo_text);
		}
	}

	owner_name = nautilus_file_get_string_attribute (file, "owner");
	owner_index = tree_model_get_entry_index (model, 0, owner_name);


	if (owner_index < 0 && owner_name != NULL) {
		if (users != NULL) {

			gtk_list_store_prepend (store, &iter);
			gtk_list_store_set (store, &iter,
					    0, "-",
					    1, NULL,
					    -1);
		}

		name_array = g_strsplit (owner_name, " - ", 2);
		if (name_array[1] != NULL) {
			user_name = g_strdup_printf ("%s\n%s", name_array[0], name_array[1]);
		} else {
			user_name = g_strdup (name_array[0]);
		}
		owner_index = 0;

		gtk_list_store_prepend (store, &iter);
		gtk_list_store_set (store, &iter,
				    0, owner_name,
				    1, user_name,
				    -1);

		g_free (user_name);
		g_strfreev (name_array);
	}

	gtk_combo_box_set_active (combo_box, owner_index);

	g_free (owner_name);
	g_list_free_full (users, g_free);
}
