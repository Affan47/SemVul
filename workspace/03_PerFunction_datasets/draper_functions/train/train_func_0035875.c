folder_maybe_connect_sync (CamelFolder *folder,
                           GCancellable *cancellable,
                           GError **error)
{
	CamelService *service;
	CamelStore *parent_store;
	CamelServiceConnectionStatus status;
	gboolean connect = FALSE;
	gboolean success = TRUE;


	parent_store = camel_folder_get_parent_store (folder);

	service = CAMEL_SERVICE (parent_store);
	status = camel_service_get_connection_status (service);
	connect = (status != CAMEL_SERVICE_CONNECTED);

	if (CAMEL_IS_OFFLINE_STORE (parent_store)) {
		CamelOfflineStore *offline_store;

		offline_store = CAMEL_OFFLINE_STORE (parent_store);
		if (!camel_offline_store_get_online (offline_store))
			connect = FALSE;
	}

	if (connect) {
		success = camel_service_connect_sync (
			service, cancellable, error);
	}

	return success;
}
