secret_service_store_finish (SecretService *service,
                             GAsyncResult *result,
                             GError **error)
{
	g_return_val_if_fail (service == NULL || SECRET_IS_SERVICE (service), FALSE);
	g_return_val_if_fail (g_simple_async_result_is_valid (result, G_OBJECT (service),
	                                                      secret_service_store), FALSE);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

	if (_secret_util_propagate_error (G_SIMPLE_ASYNC_RESULT (result), error))
		return FALSE;

	return TRUE;
}
