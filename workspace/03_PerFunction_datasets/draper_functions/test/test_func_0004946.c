e_auth_combo_box_update_available (EAuthComboBox *combo_box,
                                   GList *available_authtypes)
{
	GtkComboBox *gtk_combo_box;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gint active_index;
	gint available_index = -1;
	gint index = 0;
	gboolean iter_set;

	g_return_if_fail (E_IS_AUTH_COMBO_BOX (combo_box));

	gtk_combo_box = GTK_COMBO_BOX (combo_box);
	model = gtk_combo_box_get_model (gtk_combo_box);
	active_index = gtk_combo_box_get_active (gtk_combo_box);

	iter_set = gtk_tree_model_get_iter_first (model, &iter);

	while (iter_set) {
		CamelServiceAuthType *authtype;
		gboolean available;

		gtk_tree_model_get (
			model, &iter, COLUMN_AUTHTYPE, &authtype, -1);

		available = (g_list_find (
			available_authtypes, authtype) != NULL);

		gtk_list_store_set (
			GTK_LIST_STORE (model), &iter,
			COLUMN_STRIKETHROUGH, !available, -1);

		if (index == active_index && !available)
			active_index = -1;

		if (available && available_index == -1)
			available_index = index;

		iter_set = gtk_tree_model_iter_next (model, &iter);
		index++;
	}


	if (active_index == -1 && available_index != -1)
		gtk_combo_box_set_active (gtk_combo_box, available_index);
}
