load_file_ready_cb (void     **buffer,
		    gsize      count,
		    GError    *error,
		    gpointer   user_data)
{
	GthDeleteMetadataTask *self = user_data;
	GFile                 *file;
	void                  *tmp_buffer;

	if (error != NULL) {
		gth_task_completed (GTH_TASK (self), error);
		return;
	}

	file = self->priv->current->data;

	tmp_buffer = *buffer;
	*buffer = NULL;

	gth_hook_invoke ("delete-metadata", file, &tmp_buffer, &count);

	_g_file_write_async (file,
			     tmp_buffer,
	    		     count,
	    		     TRUE,
	    		     G_PRIORITY_DEFAULT,
	    		     gth_task_get_cancellable (GTH_TASK (self)),
			     write_file_ready_cb,
			     self);
}
