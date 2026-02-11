ves_icall_System_IO_MonoIO_DuplicateHandle (HANDLE source_process_handle, HANDLE source_handle,
		HANDLE target_process_handle, HANDLE *target_handle, gint32 access, gint32 inherit, gint32 options, gint32 *error)
{

	gboolean ret;

	MONO_PREPARE_BLOCKING;
	ret=DuplicateHandle (source_process_handle, source_handle, target_process_handle, target_handle, access, inherit, options);
	MONO_FINISH_BLOCKING;

	if(ret==FALSE) {
		*error = GetLastError ();

		return(FALSE);
	}

	return(TRUE);
}
