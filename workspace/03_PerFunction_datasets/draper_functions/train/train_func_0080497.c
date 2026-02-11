photoset_list_ready_cb (GObject      *source_object,
			GAsyncResult *res,
			gpointer      user_data)
{
	DialogData *data = user_data;
	GError     *error = NULL;
	GList      *scan;

	_g_object_list_unref (data->photosets);
	data->photosets = flickr_service_list_photosets_finish (FLICKR_SERVICE (source_object), res, &error);
	if (error != NULL) {
		if (data->service != NULL)
			gth_task_dialog (GTH_TASK (data->service), TRUE, NULL);
		_gtk_error_dialog_from_gerror_run (GTK_WINDOW (data->browser), _("Could not connect to the server"), error);
		g_clear_error (&error);
		gtk_dialog_response (GTK_DIALOG (data->dialog), GTK_RESPONSE_DELETE_EVENT);
		return;
	}

	gtk_list_store_clear (GTK_LIST_STORE (GET_WIDGET ("photoset_liststore")));
	for (scan = data->photosets; scan; scan = scan->next) {
		FlickrPhotoset *photoset = scan->data;
		char           *n_photos;
		GtkTreeIter     iter;

		n_photos = g_strdup_printf ("(%d)", photoset->n_photos);

		gtk_list_store_append (GTK_LIST_STORE (GET_WIDGET ("photoset_liststore")), &iter);
		gtk_list_store_set (GTK_LIST_STORE (GET_WIDGET ("photoset_liststore")), &iter,
				    PHOTOSET_DATA_COLUMN, photoset,
				    PHOTOSET_ICON_COLUMN, "file-catalog",
				    PHOTOSET_TITLE_COLUMN, photoset->title,
				    PHOTOSET_N_PHOTOS_COLUMN, n_photos,
				    -1);

		g_free (n_photos);
	}

	gtk_widget_set_sensitive (GET_WIDGET ("upload_button"), TRUE);

	gth_task_dialog (GTH_TASK (data->service), TRUE, NULL);

	gtk_window_set_transient_for (GTK_WINDOW (data->dialog), GTK_WINDOW (data->browser));
	gtk_window_set_modal (GTK_WINDOW (data->dialog), FALSE);
	gtk_window_present (GTK_WINDOW (data->dialog));
}
