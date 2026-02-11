transform_current_file (GthTransformTask *self)
{
	GFile *file;
	GList *singleton;

	if (self->priv->current == NULL) {
		gth_task_completed (GTH_TASK (self), NULL);
		return;
	}

	file = self->priv->current->data;
	singleton = g_list_append (NULL, g_object_ref (file));
	_g_query_all_metadata_async (singleton,
				     GTH_LIST_DEFAULT,
				     "*",
				     gth_task_get_cancellable (GTH_TASK (self)),
				     file_info_ready_cb,
				     self);

	_g_object_list_unref (singleton);
}
