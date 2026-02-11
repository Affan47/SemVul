e_mail_store_prepare_for_offline (CamelStore *store,
                                  gint io_priority,
                                  GCancellable *cancellable,
                                  GAsyncReadyCallback callback,
                                  gpointer user_data)
{
	GSimpleAsyncResult *simple;

	g_return_if_fail (CAMEL_IS_STORE (store));

	simple = g_simple_async_result_new (
		G_OBJECT (store), callback, user_data,
		e_mail_store_prepare_for_offline);

	g_simple_async_result_set_check_cancellable (simple, cancellable);

	g_simple_async_result_run_in_thread (
		simple, mail_store_prepare_for_offline_thread,
		io_priority, cancellable);

	g_object_unref (simple);
}
