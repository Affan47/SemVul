continue_loading_image (GthLoadImageInfoTask *self)
{
	if (strcmp (self->priv->attributes, "") != 0) {
		GthImageInfo *image_info;
		GList        *files;

		image_info = self->priv->images[self->priv->current];
		files = g_list_prepend (NULL, image_info->file_data);
		_g_query_metadata_async (files,
					 self->priv->attributes,
					 gth_task_get_cancellable (GTH_TASK (self)),
					 metadata_ready_cb,
					 self);

		g_list_free (files);
	}
	else
		load_next_image (self);
}
