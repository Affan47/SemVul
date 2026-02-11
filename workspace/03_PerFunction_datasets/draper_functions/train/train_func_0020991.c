action_combo_box_changed (GtkComboBox *combo_box)
{
	GtkRadioAction *action;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gint value;


	if (!gtk_combo_box_get_active_iter (combo_box, &iter))
		return;

	model = gtk_combo_box_get_model (combo_box);
	gtk_tree_model_get (model, &iter, COLUMN_ACTION, &action, -1);
	g_object_get (action, "value", &value, NULL);
	gtk_radio_action_set_current_value (action, value);
	g_object_unref (action);
}
