ok_button_clicked_cb (GtkWidget  *widget,
		      DialogData *data)
{
	GtkTreeIter  iter;
	char        *mime_type;
	GthTask     *convert_task;
	GthTask     *list_task;

	gtk_combo_box_get_active_iter (GTK_COMBO_BOX (GET_WIDGET ("mime_type_combobox")), &iter);
	gtk_tree_model_get (GTK_TREE_MODEL (GET_WIDGET ("mime_type_liststore")), &iter,
			    MIME_TYPE_COLUMN_TYPE, &mime_type,
			    -1);
	g_settings_set_string (data->settings, PREF_CONVERT_FORMAT_MIME_TYPE, mime_type);

	convert_task = gth_image_task_new (_("Converting images"),
					    NULL,
					    exec_convert,
					    NULL,
					    NULL,
					    NULL);
	list_task = gth_image_list_task_new (data->browser,
					     data->file_list,
					     GTH_IMAGE_TASK (convert_task));
	gth_image_list_task_set_overwrite_mode (GTH_IMAGE_LIST_TASK (list_task), GTH_OVERWRITE_ASK);
	gth_image_list_task_set_output_mime_type (GTH_IMAGE_LIST_TASK (list_task), mime_type);
	if (data->use_destination) {
		GFile *destination;

		destination = gtk_file_chooser_get_file (GTK_FILE_CHOOSER (GET_WIDGET ("destination_filechooserbutton")));
		gth_image_list_task_set_destination (GTH_IMAGE_LIST_TASK (list_task), destination);

		g_object_unref (destination);
	}
	gth_browser_exec_task (data->browser, list_task, FALSE);

	g_object_unref (list_task);
	g_object_unref (convert_task);
	g_free (mime_type);
	gtk_widget_destroy (data->dialog);
}
