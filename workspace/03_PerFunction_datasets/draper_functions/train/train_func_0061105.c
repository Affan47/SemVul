start_thread_test_sync (ThreadData *data)
{
	EBookQuery   *query;
	gchar        *sexp;
	GError *error = NULL;

	query = e_book_query_any_field_contains ("");
	sexp = e_book_query_to_string (query);

	if (!e_book_client_get_view_sync (data->client, sexp,
					  &(data->view), NULL, &error))
		g_error ("Error getting view: %s", error->message);

	g_signal_connect (data->view, "objects-added", G_CALLBACK (objects_added), data);
	g_signal_connect (data->view, "objects-modified", G_CALLBACK (objects_modified), data);
	g_signal_connect (data->view, "objects-removed", G_CALLBACK (objects_removed), data);
	g_signal_connect (data->view, "complete", G_CALLBACK (complete), data);

	e_book_client_view_set_fields_of_interest (data->view, NULL, &error);
	if (error)
		g_error ("set fields of interest: %s", error->message);

	e_book_client_view_start (data->view, &error);
	if (error)
		g_error ("start view: %s", error->message);

	e_book_query_unref (query);
	g_free (sexp);
}
