cal_client_remove_objects_thread (GSimpleAsyncResult *simple,
                                  GObject *source_object,
                                  GCancellable *cancellable)
{
	AsyncContext *async_context;
	GError *local_error = NULL;

	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	e_cal_client_remove_objects_sync (
		E_CAL_CLIENT (source_object),
		async_context->string_list,
		async_context->mod,
		cancellable, &local_error);

	if (local_error != NULL)
		g_simple_async_result_take_error (simple, local_error);
}
