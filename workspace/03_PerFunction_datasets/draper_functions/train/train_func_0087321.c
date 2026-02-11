rb_uri_handle_recursively_async (const char *uri,
				 GCancellable *cancel,
			         RBUriRecurseFunc func,
			         gpointer user_data,
				 GDestroyNotify data_destroy)
{
	RBUriHandleRecursivelyAsyncData *data = g_new0 (RBUriHandleRecursivelyAsyncData, 1);

	rb_debug ("processing %s", uri);
	if (cancel != NULL) {
		data->cancel = g_object_ref (cancel);
	} else {
		data->cancel = g_cancellable_new ();
	}

	data->func = func;
	data->user_data = user_data;
	data->data_destroy = data_destroy;
	data->handled = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);

	data->dirs_left = g_queue_new ();
	g_queue_push_tail (data->dirs_left, g_file_new_for_uri (uri));
	_uri_handle_recursively_next_dir (data);
}
