add_mrls_finish_operation (AddMrlsOperationData *operation_data)
{


	if (g_atomic_int_dec_and_test (&(operation_data->entries_remaining)) == TRUE) {
		GSimpleAsyncResult *async_result;

		async_result = g_simple_async_result_new (G_OBJECT (operation_data->playlist), operation_data->callback, operation_data->user_data,
		                                          totem_playlist_add_mrls);
		g_simple_async_result_complete (async_result);
		g_object_unref (async_result);

		add_mrls_operation_data_free (operation_data);
	}
}
