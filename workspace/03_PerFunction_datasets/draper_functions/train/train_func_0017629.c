e_book_client_connect (ESource *source,
                       GCancellable *cancellable,
                       GAsyncReadyCallback callback,
                       gpointer user_data)
{
	GSimpleAsyncResult *simple;
	ConnectClosure *closure;
	EBookClient *client;

	g_return_if_fail (E_IS_SOURCE (source));


	closure = g_slice_new0 (ConnectClosure);
	closure->source = g_object_ref (source);

	if (G_IS_CANCELLABLE (cancellable))
		closure->cancellable = g_object_ref (cancellable);

	client = g_object_new (
		E_TYPE_BOOK_CLIENT,
		"source", source, NULL);

	simple = g_simple_async_result_new (
		G_OBJECT (client), callback,
		user_data, e_book_client_connect);

	g_simple_async_result_set_check_cancellable (simple, cancellable);

	g_simple_async_result_set_op_res_gpointer (
		simple, closure, (GDestroyNotify) connect_closure_free);

	g_async_initable_init_async (
		G_ASYNC_INITABLE (client),
		G_PRIORITY_DEFAULT, cancellable,
		book_client_connect_init_cb,
		g_object_ref (simple));

	g_object_unref (simple);
	g_object_unref (client);
}
