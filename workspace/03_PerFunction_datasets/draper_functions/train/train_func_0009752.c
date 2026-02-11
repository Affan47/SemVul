authentication_mediator_cancelled_cb (GCancellable *cancellable,
                                      gpointer user_data)
{
	GSimpleAsyncResult *simple;
	AsyncContext *async_context;

	simple = G_SIMPLE_ASYNC_RESULT (user_data);
	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	g_mutex_lock (async_context->shared_data_lock);


	if (g_queue_remove (async_context->operation_queue, simple)) {
		g_simple_async_result_complete_in_idle (simple);
		g_object_unref (simple);
	}

	g_mutex_unlock (async_context->shared_data_lock);
}
