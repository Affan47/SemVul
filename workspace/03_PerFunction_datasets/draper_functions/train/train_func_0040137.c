gcr_mock_prompt_confirm_finish (GcrPrompt *prompt,
                                GAsyncResult *result,
                                GError **error)
{
	g_return_val_if_fail (g_simple_async_result_is_valid (result, G_OBJECT (prompt),
	                      gcr_mock_prompt_confirm_async), GCR_PROMPT_REPLY_CANCEL);

	return g_simple_async_result_get_op_res_gboolean (G_SIMPLE_ASYNC_RESULT (result)) ?
	               GCR_PROMPT_REPLY_CONTINUE : GCR_PROMPT_REPLY_CANCEL;
}
