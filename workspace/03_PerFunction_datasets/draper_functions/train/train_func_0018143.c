FlushFileBuffers(gpointer handle)
{
	WapiHandleType type;

	type = _wapi_handle_type (handle);

	if(io_ops[type].flushfile==NULL) {
		SetLastError (ERROR_INVALID_HANDLE);
		return(FALSE);
	}

	return(io_ops[type].flushfile (handle));
}
