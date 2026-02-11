contact_ready_cb (GObject *source_object,
                  GAsyncResult *result,
                  gpointer user_data)
{
	GMainLoop *loop = (GMainLoop *) user_data;
	EContact *contact;
	GError *error = NULL;

	if (!e_book_client_get_contact_finish (E_BOOK_CLIENT (source_object), result, &contact, &error)) {
		g_error ("get contact finish: %s", error->message);
	}

	g_object_unref (contact);
	g_main_loop_quit (loop);
}
