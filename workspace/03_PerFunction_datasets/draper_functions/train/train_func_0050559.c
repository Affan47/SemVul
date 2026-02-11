gcr_mock_prompt_password_finish (GcrPrompt *prompt,
                                 GAsyncResult *result,
                                 GError **error)
{
	g_return_val_if_fail (g_simple_async_result_is_valid (result, G_OBJECT (prompt),
	                      gcr_mock_prompt_password_async), NULL);

	return g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (result));

}
