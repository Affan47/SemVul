e_ews_backend_ref_connection_finish (EEwsBackend *backend,
                                     GAsyncResult *result,
                                     GError **error)
{
	GSimpleAsyncResult *simple;
	EEwsConnection *connection;

	g_return_val_if_fail (
		g_simple_async_result_is_valid (
		result, G_OBJECT (backend),
		e_ews_backend_ref_connection), NULL);

	simple = G_SIMPLE_ASYNC_RESULT (result);

	if (g_simple_async_result_propagate_error (simple, error))
		return NULL;

	connection = g_simple_async_result_get_op_res_gpointer (simple);
	g_return_val_if_fail (E_IS_EWS_CONNECTION (connection), NULL);

	return g_object_ref (connection);
}
