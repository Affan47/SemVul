jmlist_seek_end(jmlist jml,jmlist_seek_handle *handle_ptr)
{
	jmlist_debug(__func__,"called with jml=%p and handle_ptr=%p",jml,handle_ptr);

	if( !jml ) {
		jmlist_debug(__func__,"invalid jml specified (jml=0)");
		jmlist_errno = JMLIST_ERROR_INVALID_ARGUMENT;
		jmlist_debug(__func__,"returning with failure.");
		return JMLIST_ERROR_FAILURE;
	}

	if( !handle_ptr ) {
		jmlist_debug(__func__,"invalid handle_ptr specified (handle_ptr=0)");
		jmlist_errno = JMLIST_ERROR_INVALID_ARGUMENT;
		jmlist_debug(__func__,"returning with failure.");
		return JMLIST_ERROR_FAILURE;
	}

	if( !jml->seeking ) {
		jmlist_debug(__func__,"cannot stop seeking on a list that is not being seeked");
		jmlist_errno = JMLIST_ERROR_INVALID_ARGUMENT;
		jmlist_debug(__func__,"returning with failure.");
		return JMLIST_ERROR_FAILURE;
	}

	jml->seeking = false;
	jmlist_debug(__func__,"seek flag set to %u",jml->seeking);

	jmlist_debug(__func__,"returning with success.");
	return JMLIST_ERROR_SUCCESS;
}
