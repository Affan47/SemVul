import_thread (GSimpleAsyncResult *result, AlmanahImportOperation *operation, GCancellable *cancellable)
{
	GError *error = NULL;
	ImportData *data = g_simple_async_result_get_op_res_gpointer (result);


	if (g_cancellable_set_error_if_cancelled (cancellable, &error) == TRUE) {
		g_simple_async_result_set_from_error (result, error);
		g_error_free (error);
		return;
	}


	if (import_modes[operation->priv->current_mode].import_func (operation, operation->priv->source, data->progress_callback,
	    data->progress_user_data, cancellable, &error) == FALSE) {
		g_simple_async_result_set_from_error (result, error);
		g_error_free (error);
	}
}
