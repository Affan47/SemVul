gth_image_print_job_load_metadata (GthImagePrintJob *self)
{
	GList *files;
	int    i;

	files = NULL;
	for (i = 0; i < self->priv->n_images; i++)
		files = g_list_prepend (files, self->priv->images[i]->file_data);
	files = g_list_reverse (files);

	_g_query_metadata_async (files,
				 self->priv->caption_attributes,
				 NULL,
				 metadata_ready_cb,
				 self);

	g_list_free (files);
}
