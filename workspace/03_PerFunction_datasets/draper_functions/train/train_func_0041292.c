treeview_selection_changed_cb (GtkTreeSelection *treeselection,
			       gpointer          user_data)
{
	BluetoothChooserCombo *combo = BLUETOOTH_CHOOSER_COMBO (user_data);
	GtkTreeIter iter;
	char *value = NULL;

	if (gtk_tree_selection_get_selected (combo->priv->selection, NULL, &iter)) {
		gtk_combo_box_set_active_iter (GTK_COMBO_BOX (combo->priv->drop), &iter);
		if (combo->priv->model != NULL)
			gtk_tree_model_get (GTK_TREE_MODEL (combo->priv->model), &iter,
					    BLUETOOTH_COLUMN_ADDRESS, &value, -1);
	} else {
		if (combo->priv->model != NULL)
			gtk_combo_box_set_active (GTK_COMBO_BOX (combo->priv->drop), -1);
	}

	if (g_strcmp0 (combo->priv->bdaddr, value) != 0) {
		g_free (combo->priv->bdaddr);
		combo->priv->bdaddr = value;
		g_object_notify (G_OBJECT (combo), "device");
	} else {
		g_free (value);
	}
}
