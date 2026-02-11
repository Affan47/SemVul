prefs_account_compose_default_dictionary_set_optmenu_from_string
							(PrefParam *pparam)
{
	GtkWidget *combo;
	gchar *dictionary;

	cm_return_if_fail(*pparam->widget != NULL);

	dictionary = *((gchar **) pparam->data);
	if (dictionary != NULL) {
		if (strrchr(dictionary, '/')) {
			dictionary = g_strdup(strrchr(dictionary, '/')+1);
		}

		if (strchr(dictionary, '-')) {
			*(strchr(dictionary, '-')) = '\0';
		}
	}
	combo = *pparam->widget;
	if (dictionary && *dictionary)
		gtkaspell_set_dictionary_menu_active_item(GTK_COMBO_BOX(combo),
							  dictionary);
	else {
		GtkTreeModel *model;
		GtkTreeIter iter;
		if((model = gtk_combo_box_get_model(GTK_COMBO_BOX(combo))) == NULL)
			return;
		if((gtk_tree_model_get_iter_first(model, &iter)) == FALSE)
			return;
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(combo), &iter);
	}
}
