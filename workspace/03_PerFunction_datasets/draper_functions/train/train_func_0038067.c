nntp_store_folder_is_subscribed (CamelSubscribable *subscribable,
                                 const gchar *folder_name)
{
	CamelNNTPStore *nntp_store;
	CamelNNTPStoreSummary *nntp_store_summary;
	CamelStoreSummary *store_summary;
	CamelStoreInfo *si;
	gint truth = FALSE;

	nntp_store = CAMEL_NNTP_STORE (subscribable);
	nntp_store_summary = camel_nntp_store_ref_summary (nntp_store);

	store_summary = CAMEL_STORE_SUMMARY (nntp_store_summary);
	si = camel_store_summary_path (store_summary, folder_name);

	if (si != NULL) {
		truth = (si->flags & CAMEL_STORE_INFO_FOLDER_SUBSCRIBED) != 0;
		camel_store_summary_info_unref (store_summary, si);
	}

	g_clear_object (&nntp_store_summary);

	return truth;
}
