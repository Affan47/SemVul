e_cal_client_create_object (ECalClient *client,
                            icalcomponent *icalcomp,
                            GCancellable *cancellable,
                            GAsyncReadyCallback callback,
                            gpointer user_data)
{
	GSimpleAsyncResult *simple;
	AsyncContext *async_context;

	g_return_if_fail (E_IS_CAL_CLIENT (client));
	g_return_if_fail (icalcomp != NULL);

	async_context = g_slice_new0 (AsyncContext);
	async_context->in_comp = icalcomponent_new_clone (icalcomp);

	simple = g_simple_async_result_new (
		G_OBJECT (client), callback, user_data,
		e_cal_client_create_object);

	g_simple_async_result_set_op_res_gpointer (
		simple, async_context, (GDestroyNotify) async_context_free);

	g_simple_async_result_run_in_thread (
		simple, cal_client_create_object_thread,
		G_PRIORITY_DEFAULT, cancellable);

	g_object_unref (simple);
}
