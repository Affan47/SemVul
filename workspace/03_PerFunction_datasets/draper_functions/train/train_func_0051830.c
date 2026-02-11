about_button_clicked_cb (GtkButton *button,
			 gpointer   user_data)
{
	BrowserData             *data = user_data;
	GtkTreeModel            *model;
	GtkTreeIter              iter;
	GthExtensionDescription *description;
	GtkWidget               *dialog;

	model = GTK_TREE_MODEL (data->model_filter);
	if (! gtk_tree_selection_get_selected (gtk_tree_view_get_selection (GTK_TREE_VIEW (data->list_view)), &model, &iter))
		return;

	gtk_tree_model_get (model, &iter, EXTENSION_DESCRIPTION_COLUMN, &description, -1);

	dialog = gtk_about_dialog_new ();
	if (description->name != NULL)
		g_object_set (dialog, "program-name", description->name, NULL);
	if (description->description != NULL)
		g_object_set (dialog, "comments", description->description, NULL);
	if (description->version != NULL)
		g_object_set (dialog, "version", description->version, NULL);
	if (description->authors != NULL)
		g_object_set (dialog, "authors", description->authors, NULL);
	if (description->copyright != NULL)
		g_object_set (dialog, "copyright", description->copyright, NULL);
	if (description->icon_name != NULL)
		g_object_set (dialog, "logo-icon-name", description->icon_name, NULL);
	else
		g_object_set (dialog, "logo-icon-name", DEFAULT_ICON, NULL);
	if (description->url != NULL)
		g_object_set (dialog, "website", description->url, NULL);

	gtk_window_set_transient_for (GTK_WINDOW (dialog), GTK_WINDOW (data->dialog));
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

	g_object_unref (description);
}
