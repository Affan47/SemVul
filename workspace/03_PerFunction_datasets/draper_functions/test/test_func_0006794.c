pk_client_search_groups (PkClient *client, PkBitfield filters, gchar **values, GCancellable *cancellable,
			PkProgressCallback progress_callback, gpointer progress_user_data, GError **error)
{
	PkClientHelper helper;
	PkResults *results;

	g_return_val_if_fail (PK_IS_CLIENT (client), NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, NULL);


	memset (&helper, 0, sizeof (PkClientHelper));
	helper.context = g_main_context_new ();
	helper.loop = g_main_loop_new (helper.context, FALSE);
	helper.error = error;

	g_main_context_push_thread_default (helper.context);


	pk_client_search_groups_async (client, filters, values, cancellable, progress_callback, progress_user_data,
				      (GAsyncReadyCallback) pk_client_generic_finish_sync, &helper);

	g_main_loop_run (helper.loop);

	results = helper.results;

	g_main_context_pop_thread_default (helper.context);


	g_main_loop_unref (helper.loop);
	g_main_context_unref (helper.context);

	return results;
}
