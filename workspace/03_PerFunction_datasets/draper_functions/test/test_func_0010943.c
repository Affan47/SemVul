soup_test_session_abort_unref (SoupSession *session)
{
	g_object_add_weak_pointer (G_OBJECT (session), (gpointer *)&session);

	soup_session_abort (session);
	g_object_unref (session);

	if (session) {
		errors++;
		debug_printf (1, "leaked SoupSession!\n");
		g_object_remove_weak_pointer (G_OBJECT (session), (gpointer *)&session);
	}
}
