secret_item_delete_finish (SecretItem *self,
                           GAsyncResult *result,
                           GError **error)
{
	GSimpleAsyncResult *res;

	g_return_val_if_fail (SECRET_IS_ITEM (self), FALSE);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);
	g_return_val_if_fail (g_simple_async_result_is_valid (result, G_OBJECT (self),
	                      secret_item_delete), FALSE);

	res = G_SIMPLE_ASYNC_RESULT (result);

	if (_secret_util_propagate_error (res, error))
		return FALSE;

	return g_simple_async_result_get_op_res_gboolean (res);
}
