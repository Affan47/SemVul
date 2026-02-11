file_info_ready_cb (GList    *files,
		    GError   *error,
		    gpointer  user_data)
{
	GthResetOrientationTask *self = user_data;
	GthMetadata         *metadata;

	if (error != NULL) {
		gth_task_completed (GTH_TASK (self), error);
		return;
	}

	_g_object_unref (self->priv->file_data);
	self->priv->file_data = g_object_ref ((GthFileData *) files->data);

	gth_task_progress (GTH_TASK (self),
			   _("Saving images"),
			   g_file_info_get_display_name (self->priv->file_data->info),
			   FALSE,
			   (double) (self->priv->n_image + 1) / (self->priv->n_images + 1));

	metadata = g_object_new (GTH_TYPE_METADATA, "raw", "1", NULL);
	g_file_info_set_attribute_object (self->priv->file_data->info, "Exif::Image::Orientation", G_OBJECT (metadata));

	_g_write_metadata_async (files,
				 GTH_METADATA_WRITE_FORCE_EMBEDDED,
				 "*",
				 gth_task_get_cancellable (GTH_TASK (self)),
				 write_metadata_ready_cb,
				 self);

	g_object_unref (metadata);
}
