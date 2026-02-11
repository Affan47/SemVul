test_client (ETestServerFixture *fixture,
             gconstpointer user_data)
{
	EBookClient *book_client;

	book_client = E_TEST_SERVER_UTILS_SERVICE (fixture, EBookClient);


	if (!add_contact_from_test_case_verify (book_client, "custom-1", NULL) ||
	    !add_contact_from_test_case_verify (book_client, "custom-2", NULL) ||
	    !add_contact_from_test_case_verify (book_client, "custom-3", NULL) ||
	    !add_contact_from_test_case_verify (book_client, "custom-4", NULL) ||
	    !add_contact_from_test_case_verify (book_client, "custom-5", NULL) ||
	    !add_contact_from_test_case_verify (book_client, "custom-6", NULL)) {
		g_object_unref (book_client);
		g_error ("Failed to add contacts");
	}

	count_all_contacts (book_client);
	count_all_uids (book_client);

	g_assert_cmpint (fetched_contacts, ==, N_CONTACTS);
	g_assert_cmpint (fetched_uids, ==, N_CONTACTS);
}
