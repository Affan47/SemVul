select_main_group (OobsUser *user)
{
	GtkWidget *combo;
	GtkTreeModel *model;
	GtkTreeIter iter;
	OobsGroup *main_group, *group;
	gboolean valid, found;

	combo = gst_dialog_get_widget (tool->main_dialog, "user_settings_group");

	main_group = oobs_user_get_main_group (user);

	if (!main_group) {
		gtk_combo_box_set_active (GTK_COMBO_BOX (combo), -1);
		return;
	}

	found = FALSE;

	model = gtk_combo_box_get_model (GTK_COMBO_BOX (combo));
	valid = gtk_tree_model_get_iter_first (model, &iter);

	while (valid && !found) {
		gtk_tree_model_get (model, &iter,
				    COL_GROUP_OBJECT, &group,
				    -1);

		if (main_group == group) {
			gtk_combo_box_set_active_iter (GTK_COMBO_BOX (combo), &iter);
			found = TRUE;
		}

		g_object_unref (group);
		valid = gtk_tree_model_iter_next (model, &iter);
	}

	if (!found)
		gtk_combo_box_set_active (GTK_COMBO_BOX (combo), -1);
}
