e_gdbus_proxy_finish_call_string (EGdbusAsyncOpKeeper *proxy,
                                  GAsyncResult *result,
                                  gchar **out_string,
                                  GError **error,
                                  gpointer source_tag)
{
	AsyncOpData *op_data;

	g_return_val_if_fail (proxy != NULL, FALSE);
	g_return_val_if_fail (g_simple_async_result_is_valid (result, G_OBJECT (proxy), source_tag), FALSE);
	g_return_val_if_fail (out_string != NULL, FALSE);

	if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (result), error))
		return FALSE;

	op_data = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (result));
	g_return_val_if_fail (op_data != NULL, FALSE);
	g_return_val_if_fail (op_data->result_type == E_GDBUS_TYPE_STRING, FALSE);

	*out_string = op_data->result.out_string;
	op_data->result.out_string = NULL;

	return TRUE;
}
