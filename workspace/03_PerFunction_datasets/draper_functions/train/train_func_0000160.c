connection_cb (GObject      *object,
               GAsyncResult *res,
               gpointer      user_data)
{
	MyData *md = user_data;
	GError *error = NULL;

	md->connection = tracker_sparql_connection_get_finish (res, &error);
	g_print ("Async connection took: %.6f\n", g_timer_elapsed (md->timer, NULL));

	g_timer_start (md->timer);

	if (!error) {
		tracker_sparql_connection_query_async (md->connection,
		                                       "SELECT ?r { ?r a rdfs:Resource }",
		                                       md->cancellable,
		                                       query_cb,
		                                       md);
	} else {
		g_critical ("Could not connect: %s", error->message);
		g_error_free (error);
		g_main_loop_quit (md->loop);
	}
}
