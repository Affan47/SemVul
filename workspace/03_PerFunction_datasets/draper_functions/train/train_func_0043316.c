update_preview__step2 (GError   *error,
		       gpointer  user_data)
{
	DialogData *data = user_data;
	GList      *scan1, *scan2;

	if (error != NULL) {
		GtkWidget *d;

		d = _gtk_message_dialog_new (GTK_WINDOW (data->dialog),
					     GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
					     GTK_STOCK_DIALOG_ERROR,
					     _("Could not rename the files"),
					     error->message,
					     GTK_STOCK_OK, GTK_RESPONSE_OK,
					     NULL);
		g_signal_connect (d, "response", G_CALLBACK (error_dialog_response_cb), data);
		gtk_window_present (GTK_WINDOW (d));

		return;
	}


	gtk_list_store_clear (data->list_store);
	for (scan1 = data->new_file_list, scan2 = data->new_names_list;
	     scan1 && scan2;
	     scan1 = scan1->next, scan2 = scan2->next)
	{
		GthFileData *file_data1 = scan1->data;
		GthFileData *new_name = scan2->data;
		GtkTreeIter  iter;

		gtk_list_store_append (data->list_store, &iter);
		gtk_list_store_set (data->list_store, &iter,
				    PREVIEW_OLD_NAME_COLUMN, g_file_info_get_display_name (file_data1->info),
				    PREVIEW_NEW_NAME_COLUMN, new_name,
				    -1);
	}
}
