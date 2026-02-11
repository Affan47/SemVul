file_info_ready_cb (GList    *files,
		    GError   *error,
		    gpointer  user_data)
{
	GthTransformTask *self = user_data;

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

	apply_transformation_async (self->priv->file_data,
				    self->priv->transform,
				    self->priv->default_action,
				    gth_task_get_cancellable (GTH_TASK (self)),
				    transform_file_ready_cb,
				    self);
}
