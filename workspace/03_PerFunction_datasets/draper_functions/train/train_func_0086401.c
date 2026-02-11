image_task_save_current_image (GthImageListTask *self,
			       GFile            *file,
			       gboolean          replace)
{
	GthImage *destination;

	if (file != NULL)
		gth_file_data_set_file (self->priv->destination_file_data, file);

	destination = gth_image_task_get_destination (GTH_IMAGE_TASK (self->priv->task));
	if (destination == NULL) {
		process_next_file (self);
		return;
	}


	g_object_ref (destination);
	_g_object_unref (self->priv->new_image);
	self->priv->new_image = destination;

	gth_image_save_to_file (self->priv->new_image,
				gth_file_data_get_mime_type (self->priv->destination_file_data),
				self->priv->destination_file_data,
				replace,
				gth_task_get_cancellable (GTH_TASK (self)),
				image_saved_cb,
				self);
}
