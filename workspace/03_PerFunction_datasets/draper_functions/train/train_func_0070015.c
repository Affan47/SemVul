test_modify_contact_sync (ETestServerFixture *fixture,
                          gconstpointer user_data)
{
	EBookClient *book_client;
	GError *error = NULL;
	EContact *contact, *book_contact;

	book_client = E_TEST_SERVER_UTILS_SERVICE (fixture, EBookClient);

	if (!add_contact_from_test_case_verify (book_client, "name-only", &contact))
		g_error ("Failed to add contact");

	verify_premodify_and_prepare_contact (contact);

	if (!e_book_client_modify_contact_sync (book_client, contact, NULL, &error))
		g_error ("modify contact sync: %s", error->message);

	if (!e_book_client_get_contact_sync (book_client, e_contact_get_const (contact, E_CONTACT_UID),
					     &book_contact, NULL, &error))
		g_error ("get contact sync: %s", error->message);

	verify_modify (book_contact);
	g_object_unref (book_contact);
	g_object_unref (contact);
}
