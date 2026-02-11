ves_icall_System_IO_MonoIO_Seek (HANDLE handle, gint64 offset, gint32 origin,
				 gint32 *error)
{
	gint32 offset_hi;
	MONO_PREPARE_BLOCKING;

	*error=ERROR_SUCCESS;

	offset_hi = offset >> 32;
	offset = SetFilePointer (handle, (gint32) (offset & 0xFFFFFFFF), &offset_hi,
				 convert_seekorigin ((MonoSeekOrigin)origin));

	if(offset==INVALID_SET_FILE_POINTER) {
		*error=GetLastError ();
	}

	MONO_FINISH_BLOCKING;
	return offset | ((gint64)offset_hi << 32);
}
