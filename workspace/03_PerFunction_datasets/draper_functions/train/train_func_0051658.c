imapx_fetch_messages_sync (CamelFolder *folder,
                           CamelFetchType type,
                           gint limit,
                           GCancellable *cancellable,
                           GError **error)
{
	CamelStore *store;
	CamelIMAPXStore *imapx_store;
	CamelIMAPXServer *imapx_server;
	gboolean success = FALSE;

	store = camel_folder_get_parent_store (folder);

	imapx_store = CAMEL_IMAPX_STORE (store);
	imapx_server = camel_imapx_store_ref_server (imapx_store, error);

	if (imapx_server != NULL) {
		success = camel_imapx_server_fetch_messages (
			imapx_server, folder, type, limit, cancellable, error);
	}

	g_clear_object (&imapx_server);

	return success;
}
