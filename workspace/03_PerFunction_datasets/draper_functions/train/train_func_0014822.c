test_preserve_uid (ETestServerFixture *fixture,
                   gconstpointer user_data)
{
	EBookClient *book_client;
	EContact    *contact;
	gchar       *vcard;
	gchar       *uid = NULL;
	GError      *error = NULL;

	book_client = E_TEST_SERVER_UTILS_SERVICE (fixture, EBookClient);

	vcard = new_vcard_from_test_case ("simple-1");
	contact = e_contact_new_from_vcard (vcard);
	g_free (vcard);

	e_contact_set (contact, E_CONTACT_UID, TEST_CONTACT_UID);

	if (!e_book_client_add_contact_sync (book_client, contact, &uid, NULL, &error))
		g_error ("Failed to add contact: %s", error->message);

	g_assert_cmpstr (uid, ==, TEST_CONTACT_UID);
	g_object_unref (contact);
	g_free (uid);
}
