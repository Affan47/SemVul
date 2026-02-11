ves_icall_System_IO_MonoIO_DeleteFile (MonoString *path, gint32 *error)
{
	gboolean ret;
	MONO_PREPARE_BLOCKING;

	*error=ERROR_SUCCESS;

	ret=DeleteFile (mono_string_chars (path));
	if(ret==FALSE) {
		*error=GetLastError ();
	}

	MONO_FINISH_BLOCKING;
	return(ret);
}
