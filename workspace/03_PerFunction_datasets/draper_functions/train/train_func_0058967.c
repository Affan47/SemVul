ui_language_combobox_get_active_id(GtkComboBox *combobox)
{
GtkTreeModel *model;
GtkTreeIter  iter;
gchar *id = 0;

	if( gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combobox), &iter) )
	{
		model = gtk_combo_box_get_model(GTK_COMBO_BOX(combobox));
		gtk_tree_model_get (GTK_TREE_MODEL(model), &iter,
				            0, &id,
				            -1);
	}

	return id;
}
