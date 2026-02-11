store_create_folder_finish (CamelStore *store,
                            GAsyncResult *result,
                            GError **error)
{
	GSimpleAsyncResult *simple;
	AsyncContext *async_context;
	CamelFolderInfo *folder_info;

	g_return_val_if_fail (
		g_simple_async_result_is_valid (
		result, G_OBJECT (store), store_create_folder), NULL);

	simple = G_SIMPLE_ASYNC_RESULT (result);
	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	if (g_simple_async_result_propagate_error (simple, error))
		return NULL;

	folder_info = async_context->folder_info;
	async_context->folder_info = NULL;

	return folder_info;
}
