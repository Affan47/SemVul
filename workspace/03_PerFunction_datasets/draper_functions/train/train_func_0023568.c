imapx_folder_dispose (GObject *object)
{
	CamelIMAPXFolder *folder = CAMEL_IMAPX_FOLDER (object);
	CamelStore *store;

	if (folder->cache != NULL) {
		g_object_unref (folder->cache);
		folder->cache = NULL;
	}

	if (folder->search != NULL) {
		g_object_unref (folder->search);
		folder->search = NULL;
	}

	store = camel_folder_get_parent_store (CAMEL_FOLDER (folder));
	if (store != NULL) {
		camel_store_summary_disconnect_folder_summary (
			(CamelStoreSummary *) ((CamelIMAPXStore *) store)->summary,
			CAMEL_FOLDER (folder)->summary);
	}


	G_OBJECT_CLASS (camel_imapx_folder_parent_class)->dispose (object);
}
