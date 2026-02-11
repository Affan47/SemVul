ves_icall_System_IO_MonoIO_SetFileAttributes (MonoString *path, gint32 attrs,
					      gint32 *error)
{
	gboolean ret;
	MONO_PREPARE_BLOCKING;

	*error=ERROR_SUCCESS;

	ret=SetFileAttributes (mono_string_chars (path),
		convert_attrs ((MonoFileAttributes)attrs));
	if(ret==FALSE) {
		*error=GetLastError ();
	}

	MONO_FINISH_BLOCKING;
	return(ret);
}
