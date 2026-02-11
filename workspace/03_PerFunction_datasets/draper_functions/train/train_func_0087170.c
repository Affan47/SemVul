gedit_encodings_dialog_init (GeditEncodingsDialog *dlg)
{
	GtkTreeIter parent_iter;
	GtkTreeSelection *selection;
	const GeditEncoding *enc;
	int i;

	dlg->priv = gedit_encodings_dialog_get_instance_private (dlg);

	dlg->priv->enc_settings = g_settings_new ("org.gnome.gedit.preferences.encodings");

	gtk_widget_init_template (GTK_WIDGET (dlg));

	gtk_dialog_set_default_response (GTK_DIALOG (dlg),
					 GTK_RESPONSE_OK);

	g_signal_connect (dlg->priv->add_button,
			  "clicked",
			  G_CALLBACK (add_button_clicked_callback),
			  dlg);
	g_signal_connect (dlg->priv->remove_button,
			  "clicked",
			  G_CALLBACK (remove_button_clicked_callback),
			  dlg);


	i = 0;
	while ((enc = gedit_encoding_get_from_index (i)) != NULL)
	{
		gtk_list_store_append (dlg->priv->available_liststore,
				       &parent_iter);
		gtk_list_store_set (dlg->priv->available_liststore,
				    &parent_iter,
				    COLUMN_CHARSET,
				    gedit_encoding_get_charset (enc),
				    COLUMN_NAME,
				    gedit_encoding_get_name (enc), -1);

		++i;
	}


	gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (dlg->priv->sort_available),
					      COLUMN_NAME,
					      GTK_SORT_ASCENDING);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (dlg->priv->available_treeview));

	available_selection_changed_callback (selection, dlg);
	g_signal_connect (selection,
			  "changed",
			  G_CALLBACK (available_selection_changed_callback),
			  dlg);


	init_shown_in_menu_tree_model (dlg);


	gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (dlg->priv->sort_displayed),
					      COLUMN_NAME,
					      GTK_SORT_ASCENDING);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (dlg->priv->displayed_treeview));

	displayed_selection_changed_callback (selection, dlg);
	g_signal_connect (selection,
			  "changed",
			  G_CALLBACK (displayed_selection_changed_callback),
			  dlg);
}
