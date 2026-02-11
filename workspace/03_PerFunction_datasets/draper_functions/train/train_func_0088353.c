store_noop_finish (CamelStore *store,
                   GAsyncResult *result,
                   GError **error)
{
	GSimpleAsyncResult *simple;

	g_return_val_if_fail (
		g_simple_async_result_is_valid (
		result, G_OBJECT (store), store_noop), FALSE);

	simple = G_SIMPLE_ASYNC_RESULT (result);


	return !g_simple_async_result_propagate_error (simple, error);
}
