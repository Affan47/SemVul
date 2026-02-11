e_book_backend_open (EBookBackend *backend,
                     GCancellable *cancellable,
                     GAsyncReadyCallback callback,
                     gpointer user_data)
{
	EBookBackendClass *class;
	GSimpleAsyncResult *simple;

	g_return_if_fail (E_IS_BOOK_BACKEND (backend));

	class = E_BOOK_BACKEND_GET_CLASS (backend);

	simple = g_simple_async_result_new (
		G_OBJECT (backend), callback,
		user_data, e_book_backend_open);

	g_simple_async_result_set_check_cancellable (simple, cancellable);

	if (class->open_sync != NULL) {
		book_backend_push_operation (
			backend, simple, cancellable, TRUE,
			book_backend_open_thread);
		book_backend_dispatch_next_operation (backend);

	} else if (class->open != NULL) {
		book_backend_push_operation (
			backend, simple, cancellable, TRUE,
			book_backend_open_thread_old_style);
		book_backend_dispatch_next_operation (backend);

	} else {
		g_simple_async_result_set_error (
			simple, E_CLIENT_ERROR,
			E_CLIENT_ERROR_NOT_SUPPORTED,
			"%s", e_client_error_to_string (
			E_CLIENT_ERROR_NOT_SUPPORTED));
		g_simple_async_result_complete_in_idle (simple);
	}

	g_object_unref (simple);
}
