save_image (GthSaveImageTask *self)
{
	char *filename;
	char *description;

	filename = g_file_get_parse_name (self->priv->file_data->file);

	description = g_strdup_printf (_("Saving '%s'"), filename);
	gth_task_progress (GTH_TASK (self), description, NULL, TRUE, 0.0);

	gth_image_save_to_file (self->priv->image,
			        self->priv->mime_type,
			        self->priv->file_data,
			        ((self->priv->overwrite_mode == GTH_OVERWRITE_RESPONSE_YES)
			         || (self->priv->overwrite_mode == GTH_OVERWRITE_RESPONSE_ALWAYS_YES)),
			        gth_task_get_cancellable (GTH_TASK (self)),
			        save_to_file_ready_cb,
			        self);

	g_free (description);
	g_free (filename);
}
