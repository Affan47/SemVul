cal_backend_get_object_list_thread (GSimpleAsyncResult *simple,
                                    GObject *source_object,
                                    GCancellable *cancellable)
{
	ECalBackend *backend;
	ECalBackendClass *class;
	EDataCal *data_cal;
	AsyncContext *async_context;

	backend = E_CAL_BACKEND (source_object);

	class = E_CAL_BACKEND_GET_CLASS (backend);
	g_return_if_fail (class->get_object_list != NULL);

	data_cal = e_cal_backend_ref_data_cal (backend);
	g_return_if_fail (data_cal != NULL);

	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	if (!e_cal_backend_is_opened (backend)) {
		g_simple_async_result_set_error (
			simple, E_CLIENT_ERROR,
			E_CLIENT_ERROR_NOT_OPENED,
			"%s", e_client_error_to_string (
			E_CLIENT_ERROR_NOT_OPENED));
		g_simple_async_result_complete_in_idle (simple);

	} else {
		guint32 opid;

		opid = cal_backend_stash_operation (backend, simple);

		class->get_object_list (
			backend, data_cal, opid, cancellable,
			async_context->query);
	}

	g_object_unref (data_cal);
}
