save_image_preview_ready_cb (GthFileData *file_data,
			     GError      *error,
			     gpointer     data)
{
	GthWebExporter *self = data;

	if (error != NULL) {
		cleanup_and_terminate (self, error);
		return;
	}

	self->priv->saving_timeout = g_idle_add (load_next_file_cb, self);
}
