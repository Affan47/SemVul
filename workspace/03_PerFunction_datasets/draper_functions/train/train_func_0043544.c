e_user_prompter_extension_prompt_finish (EUserPrompter *prompter,
                                         GAsyncResult *result,
                                         ENamedParameters *out_values,
                                         GError **error)
{
	GSimpleAsyncResult *simple;
	PrompterAsyncData *async_data;

	g_return_val_if_fail (E_IS_USER_PROMPTER (prompter), -1);
	g_return_val_if_fail (g_simple_async_result_is_valid (result, G_OBJECT (prompter), e_user_prompter_extension_prompt), FALSE);

	simple = G_SIMPLE_ASYNC_RESULT (result);
	async_data = g_simple_async_result_get_op_res_gpointer (simple);

	if (g_simple_async_result_propagate_error (simple, error))
		return -1;

	g_return_val_if_fail (async_data != NULL, -1);

	if (out_values)
		e_named_parameters_assign (out_values, async_data->out_values);

	return async_data->response_button;
}
