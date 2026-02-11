_wapi_handle_collect (void)
{
	guint32 count = _wapi_shared_layout->collection_count;
	int i, thr_ret;

	if (!_wapi_shm_enabled ())
		return;

	DEBUG ("%s: (%d) Starting a collection", __func__, _wapi_getpid ());


	thr_ret = _wapi_handle_lock_shared_handles ();
	g_assert (thr_ret == 0);

	DEBUG ("%s: (%d) Master set", __func__, _wapi_getpid ());


	if (count == _wapi_shared_layout->collection_count) {
		guint32 too_old = (guint32)(time(NULL) & 0xFFFFFFFF) - _WAPI_HANDLE_COLLECTION_EXPIRED_INTERVAL;

		for (i = 0; i < _WAPI_HANDLE_INITIAL_COUNT; i++) {
			struct _WapiHandleShared *data;

			data = &_wapi_shared_layout->handles[i];
			if (data->timestamp < too_old) {
				DEBUG ("%s: (%d) Deleting handle 0x%x", __func__, _wapi_getpid (), i);
				memset (&_wapi_shared_layout->handles[i], '\0', sizeof(struct _WapiHandleShared));
			}
		}

		for (i = 0; i < _wapi_fileshare_layout->hwm; i++) {
			struct _WapiFileShare *file_share = &_wapi_fileshare_layout->share_info[i];

			if (file_share->timestamp < too_old) {
				memset (file_share, '\0',
					sizeof(struct _WapiFileShare));
			}
		}

		InterlockedIncrement ((gint32 *)&_wapi_shared_layout->collection_count);
	}

	_wapi_handle_unlock_shared_handles ();

	DEBUG ("%s: (%d) Collection done", __func__, _wapi_getpid ());
}
