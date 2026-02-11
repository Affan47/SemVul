e_book_backend_create_contacts_finish (EBookBackend *backend,
                                       GAsyncResult *result,
                                       GQueue *out_contacts,
                                       GError **error)
{
	GSimpleAsyncResult *simple;
	AsyncContext *async_context;

	g_return_val_if_fail (
		g_simple_async_result_is_valid (
		result, G_OBJECT (backend),
		e_book_backend_create_contacts), FALSE);
	g_return_val_if_fail (out_contacts != NULL, FALSE);

	simple = G_SIMPLE_ASYNC_RESULT (result);
	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	book_backend_unblock_operations (backend, simple);

	if (g_simple_async_result_propagate_error (simple, error))
		return FALSE;

	while (!g_queue_is_empty (async_context->object_queue)) {
		EContact *contact;

		contact = g_queue_pop_head (async_context->object_queue);
		g_queue_push_tail (out_contacts, g_object_ref (contact));
		e_book_backend_notify_update (backend, contact);
		g_object_unref (contact);
	}

	e_book_backend_notify_complete (backend);

	return TRUE;
}
