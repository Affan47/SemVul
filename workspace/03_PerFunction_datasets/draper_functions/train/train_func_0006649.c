ves_icall_System_IO_MonoIO_GetFileAttributes (MonoString *path, gint32 *error)
{
	gint32 ret;
	MONO_PREPARE_BLOCKING;

	*error=ERROR_SUCCESS;

	ret=get_file_attributes (mono_string_chars (path));


	if (ret==-1) {

		*error=GetLastError ();
	}

	MONO_FINISH_BLOCKING;
	return(ret);
}
