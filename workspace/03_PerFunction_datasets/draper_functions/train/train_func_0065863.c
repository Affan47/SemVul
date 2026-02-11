count_all_uids_cb (GObject *source_object,
                   GAsyncResult *result,
                   gpointer user_data)
{
	EBookClient *book_client;
	GSList *uids = NULL;
	GError *error = NULL;
	GMainLoop *loop = (GMainLoop *) user_data;

	book_client = E_BOOK_CLIENT (source_object);
	g_return_if_fail (book_client != NULL);

	if (!e_book_client_get_contacts_uids_finish (book_client, result, &uids, &error))
		g_error ("get contacts uids finish: %s", error->message);

	fetched_uids = g_slist_length (uids);

	g_slist_foreach (uids, (GFunc) g_free, NULL);
	g_slist_free (uids);

	g_main_loop_quit (loop);
}
