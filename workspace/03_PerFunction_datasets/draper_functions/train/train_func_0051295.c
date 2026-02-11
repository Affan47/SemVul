gdata_batch_operation_run_async (GDataBatchOperation *self, GCancellable *cancellable, GAsyncReadyCallback callback, gpointer user_data)
{
	GSimpleAsyncResult *result;

	g_return_if_fail (GDATA_IS_BATCH_OPERATION (self));
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));
	g_return_if_fail (self->priv->has_run == FALSE);


	self->priv->is_async = TRUE;

	result = g_simple_async_result_new (G_OBJECT (self), callback, user_data, gdata_batch_operation_run_async);


	g_simple_async_result_set_handle_cancellation (result, FALSE);

	g_simple_async_result_run_in_thread (result, (GSimpleAsyncThreadFunc) run_thread, G_PRIORITY_DEFAULT, cancellable);
	g_object_unref (result);
}
