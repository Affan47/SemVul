file_enumerator_close_cb (GObject      *enumerator,
                          GAsyncResult *result,
                          gpointer      user_data)
{
	TrackerCrawler *crawler;
	GError *error = NULL;

	crawler = TRACKER_CRAWLER (user_data);

	if (!g_file_enumerator_close_finish (G_FILE_ENUMERATOR (enumerator),
	                                     result,
	                                     &error)) {
		g_warning ("Couldn't close GFileEnumerator (%p): %s", enumerator,
		           (error) ? error->message : "No reason");

		g_clear_error (&error);
	}


	process_func_start (crawler);
	g_object_unref (crawler);
}
