lookup_process_handle (gpointer handle)
{
	WapiHandle_process *process_data;
	gboolean ret;

	ret = _wapi_lookup_handle (handle, WAPI_HANDLE_PROCESS,
							   (gpointer *)&process_data);
	if (!ret)
		return NULL;
	return process_data;
}
