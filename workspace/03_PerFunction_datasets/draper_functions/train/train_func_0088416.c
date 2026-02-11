nntp_store_unsubscribe_folder_sync (CamelSubscribable *subscribable,
                                    const gchar *folder_name,
                                    GCancellable *cancellable,
                                    GError **error)
{
	CamelNNTPStore *nntp_store;
	CamelNNTPStoreSummary *nntp_store_summary;
	CamelStoreSummary *store_summary;
	CamelService *service;
	CamelSettings *settings;
	CamelStoreInfo *si;
	gboolean short_folder_names;
	gboolean success = TRUE;

	service = CAMEL_SERVICE (subscribable);

	settings = camel_service_ref_settings (service);

	short_folder_names = camel_nntp_settings_get_short_folder_names (
		CAMEL_NNTP_SETTINGS (settings));

	g_object_unref (settings);

	nntp_store = CAMEL_NNTP_STORE (subscribable);
	nntp_store_summary = camel_nntp_store_ref_summary (nntp_store);

	store_summary = CAMEL_STORE_SUMMARY (nntp_store_summary);
	si = camel_store_summary_path (store_summary, folder_name);

	if (si == NULL) {
		g_set_error (
			error, CAMEL_FOLDER_ERROR,
			CAMEL_FOLDER_ERROR_INVALID,
			_("You cannot unsubscribe to this newsgroup:\n\n"
			"newsgroup does not exist!"));
		success = FALSE;
	} else {
		if (si->flags & CAMEL_STORE_INFO_FOLDER_SUBSCRIBED) {
			CamelFolderInfo *fi;

			si->flags &= ~CAMEL_STORE_INFO_FOLDER_SUBSCRIBED;

			fi = nntp_folder_info_from_store_info (
				nntp_store, short_folder_names, si);

			camel_store_summary_touch (store_summary);
			camel_store_summary_save (store_summary);

			camel_subscribable_folder_unsubscribed (
				subscribable, fi);

			camel_folder_info_free (fi);
		}

		camel_store_summary_info_unref (store_summary, si);
	}

	g_clear_object (&nntp_store_summary);

	return success;
}
