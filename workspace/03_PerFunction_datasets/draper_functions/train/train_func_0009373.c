mono_async_result_new (MonoDomain *domain, HANDLE handle, MonoObject *state, gpointer data, MonoObject *object_data)
{
	MONO_REQ_GC_UNSAFE_MODE;

	MonoAsyncResult *res = (MonoAsyncResult *)mono_object_new (domain, mono_defaults.asyncresult_class);
	MonoObject *context = mono_runtime_capture_context (domain);

	if (context) {
		MONO_OBJECT_SETREF (res, execution_context, context);

	}

	res->data = (void **)data;
	MONO_OBJECT_SETREF (res, object_data, object_data);
	MONO_OBJECT_SETREF (res, async_state, state);
	if (handle != NULL)
		MONO_OBJECT_SETREF (res, handle, (MonoObject *) mono_wait_handle_new (domain, handle));

	res->sync_completed = FALSE;
	res->completed = FALSE;

	return res;
}
