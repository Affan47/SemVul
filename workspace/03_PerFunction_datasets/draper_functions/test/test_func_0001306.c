cb_display_changed (GtkComboBox *combo, GogErrorBarEditor *editor)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	GValue value;

	memset (&value, 0, sizeof (GValue));
       	model = gtk_combo_box_get_model (combo);
	gtk_combo_box_get_active_iter (combo, &iter);
	gtk_tree_model_get_value (model, &iter, 2, &value);

	editor->display = g_value_get_uint (&value);
	if (editor->bar) {
		editor->bar->display = g_value_get_uint (&value);
		gog_object_request_update (GOG_OBJECT (editor->series));
	}

	g_value_unset (&value);
}
