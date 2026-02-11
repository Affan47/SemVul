cursor_cb (GObject      *object,
           GAsyncResult *res,
           gpointer      user_data)
{
	TrackerSparqlCursor *cursor;
	GError *error = NULL;
	MyData *md = user_data;
	gboolean more_results;

	cursor = TRACKER_SPARQL_CURSOR (object);
	more_results = tracker_sparql_cursor_next_finish (cursor,
	                                                  res,
	                                                  &error);

	if (!error) {
		static gint i = 0;

		if (more_results) {
			if (i++ < 5) {
				if (i == 1) {
					g_print ("Printing first 5 results:\n");
				}

				g_print ("  %s\n", tracker_sparql_cursor_get_string (cursor, 0, NULL));

				if (i == 5) {
					g_print ("  ...\n");
					g_print ("  Printing nothing for remaining results\n");
				}
			}

			tracker_sparql_cursor_next_async (cursor,
			                                  md->cancellable,
			                                  cursor_cb,
			                                  md);
		} else {
			g_print ("\n");
			g_print ("Async cursor next took: %.6f (for all %d results)\n",
			         g_timer_elapsed (md->timer, NULL), i);

			g_object_unref (cursor);
			g_main_loop_quit (md->loop);
		}
	} else {
		g_critical ("Could not run cursor next: %s", error->message);

		if (cursor) {
			g_object_unref (cursor);
		}

		g_error_free (error);
		g_main_loop_quit (md->loop);
	}
}
