overwrite_dialog_response_cb (GtkDialog *dialog,
                              gint       response_id,
                              gpointer   user_data)
{
	GthImageListTask *self = user_data;
	gboolean          close_overwrite_dialog = TRUE;

	if (response_id != GTK_RESPONSE_OK)
		self->priv->overwrite_response = GTH_OVERWRITE_RESPONSE_CANCEL;
	else
		self->priv->overwrite_response = gth_overwrite_dialog_get_response (GTH_OVERWRITE_DIALOG (dialog));

	gtk_widget_hide (GTK_WIDGET (dialog));
	gth_task_dialog (GTH_TASK (self), FALSE, NULL);

	switch (self->priv->overwrite_response) {
	case GTH_OVERWRITE_RESPONSE_NO:
	case GTH_OVERWRITE_RESPONSE_ALWAYS_NO:
	case GTH_OVERWRITE_RESPONSE_UNSPECIFIED:
		if (self->priv->overwrite_response == GTH_OVERWRITE_RESPONSE_ALWAYS_NO)
			self->priv->overwrite_mode = GTH_OVERWRITE_SKIP;
		process_next_file (self);
		break;

	case GTH_OVERWRITE_RESPONSE_YES:
	case GTH_OVERWRITE_RESPONSE_ALWAYS_YES:
		if (self->priv->overwrite_response == GTH_OVERWRITE_RESPONSE_ALWAYS_YES)
			self->priv->overwrite_mode = GTH_OVERWRITE_OVERWRITE;
		image_task_save_current_image (self, NULL, TRUE);
		break;

	case GTH_OVERWRITE_RESPONSE_RENAME:
		{
			GFile  *parent;
			GFile  *new_destination;
			GError *error = NULL;

			if (self->priv->destination_folder != NULL)
				parent = g_object_ref (self->priv->destination_folder);
			else
				parent = g_file_get_parent (self->priv->destination_file_data->file);

			new_destination = g_file_get_child_for_display_name (parent, gth_overwrite_dialog_get_filename (GTH_OVERWRITE_DIALOG (dialog)), &error);
			if (new_destination == NULL) {
				_gtk_error_dialog_from_gerror_run (GTK_WINDOW (dialog), _("Could not rename the file"), error);
				g_clear_error (&error);
				gtk_widget_show (GTK_WIDGET (dialog));
				gth_task_dialog (GTH_TASK (self), TRUE, GTK_WIDGET (dialog));
				close_overwrite_dialog = FALSE;
			}
			else
				image_task_save_current_image (self, new_destination, FALSE);

			g_object_unref (new_destination);
			g_object_unref (parent);
		}
		break;

	case GTH_OVERWRITE_RESPONSE_CANCEL:
		{
			GError *error;

			error = g_error_new_literal (GTH_TASK_ERROR, GTH_TASK_ERROR_CANCELLED, "");
			gth_task_completed (GTH_TASK (self), error);
		}
		break;
	}

	if (close_overwrite_dialog)
		gtk_widget_destroy (GTK_WIDGET (dialog));
}
