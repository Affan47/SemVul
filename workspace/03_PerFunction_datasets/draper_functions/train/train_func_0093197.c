cdf_sync_offline (CamelSession *session,
                  GCancellable *cancellable,
                  struct _cdf_sync_data *data,
                  GError **error)
{
	camel_operation_push_message (
		cancellable,
		_("Downloading new messages for offline mode"));

	if (data->changes != NULL) {
		GPtrArray *uid_added;
		gint ii;

		uid_added = data->changes->uid_added;

		for (ii = 0; ii < uid_added->len; ii++) {
			gint pc = ii * 100 / uid_added->len;

			camel_operation_progress (cancellable, pc);
			camel_disco_folder_cache_message (
				CAMEL_DISCO_FOLDER (data->folder),
				uid_added->pdata[ii], NULL, error);
		}
	} else {
		camel_disco_folder_prepare_for_offline (
			CAMEL_DISCO_FOLDER (data->folder),
			"(match-all)", NULL, error);
	}

	camel_operation_pop_message (cancellable);
}
