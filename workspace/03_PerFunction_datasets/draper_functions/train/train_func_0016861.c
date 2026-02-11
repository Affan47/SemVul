_wapi_handle_new_internal (WapiHandleType type,
					  gpointer handle_specific)
{
	guint32 i, k, count;
	static guint32 last = 0;
	gboolean retry = FALSE;

	g_assert (_wapi_has_shut_down == FALSE);


	if (last < _wapi_fd_reserve) {
		last = _wapi_fd_reserve;
	} else {
		retry = TRUE;
	}

again:
	count = last;
	for(i = SLOT_INDEX (count); i < _wapi_private_handle_slot_count; i++) {
		if (_wapi_private_handles [i]) {
			for (k = SLOT_OFFSET (count); k < _WAPI_HANDLE_INITIAL_COUNT; k++) {
				struct _WapiHandleUnshared *handle = &_wapi_private_handles [i][k];

				if(handle->type == WAPI_HANDLE_UNUSED) {
					last = count + 1;

					_wapi_handle_init (handle, type, handle_specific);
					return (count);
				}
				count++;
			}
		}
	}

	if(retry && last > _wapi_fd_reserve) {

		last = _wapi_fd_reserve;
		goto again;
	}


	return(0);
}
