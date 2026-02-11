test_get_contact_uids_sync (ETestServerFixture *fixture,
                            gconstpointer user_data)
{
	EBookClient *book_client;
	EContact *contact = NULL;
	EBookQuery *query;
	gchar *sexp;
	GSList *contacts = NULL;
	GError *error = NULL;

	book_client = E_TEST_SERVER_UTILS_SERVICE (fixture, EBookClient);

	if (!add_contact_from_test_case_verify (book_client, "simple-1", &contact)) {
		g_error ("Failed to add contact");
	}
	g_object_unref (contact);

	query = e_book_query_field_test (E_CONTACT_FULL_NAME, E_BOOK_QUERY_IS, "Foo Bar");
	sexp = e_book_query_to_string (query);

	if (!e_book_client_get_contacts_uids_sync (book_client, sexp, &contacts, NULL, &error)) {
		g_error ("get contacts uids: %s", error->message);
	}

	g_assert_cmpint (g_slist_length (contacts), ==, 1);
	e_util_free_string_slist (contacts);

	e_book_query_unref (query);
	g_free (sexp);

}
