ebews_forget_all_contacts (EBookBackendEws *ebews)
{
	EBookBackend *backend;
	GSList *ids = NULL;

	g_return_if_fail (E_IS_BOOK_BACKEND_EWS (ebews));

	backend = E_BOOK_BACKEND (ebews);
	g_return_if_fail (backend != NULL);

	ids = e_book_backend_sqlitedb_search_uids (ebews->priv->summary, ebews->priv->folder_id, NULL, NULL, NULL);
	if (ids) {
		GSList *id;

		e_book_backend_sqlitedb_remove_contacts (ebews->priv->summary, ebews->priv->folder_id, ids, NULL);
		for (id = ids; id; id = id->next) {
			e_book_backend_notify_remove (backend, id->data);
		}

		g_slist_free_full (ids, g_free);
	}
}
