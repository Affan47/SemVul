source_authenticator_try_password_finish (ESourceAuthenticator *auth,
                                          GAsyncResult *result,
                                          GError **error)
{
	GSimpleAsyncResult *simple;
	AsyncContext *async_context;

	g_return_val_if_fail (
		g_simple_async_result_is_valid (
		result, G_OBJECT (auth),
		source_authenticator_try_password),
		E_SOURCE_AUTHENTICATION_REJECTED);

	simple = G_SIMPLE_ASYNC_RESULT (result);
	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	if (g_simple_async_result_propagate_error (simple, error))
		return E_SOURCE_AUTHENTICATION_ERROR;

	return async_context->result;
}
