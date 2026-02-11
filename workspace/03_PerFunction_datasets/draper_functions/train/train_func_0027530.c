gdb_on_printer_add (GtkButton *button, gpointer user_data)
{
	PreferenceDialog *dlg = (PreferenceDialog *)user_data;
	GtkWidget *chooser;
	GtkFileFilter *filter;

	chooser = gtk_file_chooser_dialog_new (_("Select a pretty printer file"),
					GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (button))),
					GTK_FILE_CHOOSER_ACTION_OPEN,
					GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					NULL);
	filter = gtk_file_filter_new ();
	gtk_file_filter_add_mime_type (filter, "text/x-python");
	gtk_file_chooser_set_select_multiple (GTK_FILE_CHOOSER (chooser), TRUE);
	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (chooser),filter);

	if (gtk_dialog_run (GTK_DIALOG (chooser)) == GTK_RESPONSE_ACCEPT)
	{
		GSList *filenames;
		GSList *item;

		filenames = gtk_file_chooser_get_filenames (GTK_FILE_CHOOSER (chooser));

		for (item = filenames; item != NULL; item = g_slist_next (item))
		{
			GtkTreeIter iter;
			gchar *path = (gchar *)item->data;
			gchar *function;

			function = gdb_find_register_function (path);

			gtk_list_store_append (dlg->model, &iter);
			gtk_list_store_set (dlg->model, &iter, GDB_PP_ACTIVE_COLUMN, TRUE,
												GDB_PP_FILENAME_COLUMN, path,
												GDB_PP_REGISTER_COLUMN, function,
												-1);
			g_free (path);
			g_free (function);

			gdb_check_register_function (dlg, &iter);
		}
		g_slist_free (filenames);
	}
	gtk_widget_destroy (chooser);
}
