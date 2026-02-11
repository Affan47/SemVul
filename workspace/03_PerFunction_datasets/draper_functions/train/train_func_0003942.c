thread_lookup_certificate (GSimpleAsyncResult *res, GObject *object, GCancellable *cancel)
{
	lookup_issuer_closure *closure;
	GError *error = NULL;

	closure = g_simple_async_result_get_op_res_gpointer (res);
	closure->result = perform_lookup_certificate (closure->search, cancel, &error);

	if (error != NULL) {
		g_simple_async_result_set_from_error (res, error);
		g_clear_error (&error);
	}
}
