process_open_compare (gpointer handle, gpointer user_data)
{
	pid_t wanted_pid;
	WapiHandle_process *process_handle;
	pid_t checking_pid;

	g_assert (!WAPI_IS_PSEUDO_PROCESS_HANDLE (handle));

	process_handle = lookup_process_handle (handle);
	g_assert (process_handle);

	DEBUG ("%s: looking at process %d", __func__, process_handle->id);

	checking_pid = process_handle->id;

	if (checking_pid == 0)
		return FALSE;

	wanted_pid = GPOINTER_TO_UINT (user_data);


	if (checking_pid == wanted_pid &&
	    !_wapi_handle_issignalled (handle)) {


		return TRUE;
	} else {
		return FALSE;
	}
}
