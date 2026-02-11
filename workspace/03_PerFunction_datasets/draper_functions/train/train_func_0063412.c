test_photo_has_photo (gconstpointer service)
{
	GDataContactsContact *contact;
	gsize length = 0;
	gchar *content_type = NULL;
	GError *error = NULL;

	contact = GDATA_CONTACTS_CONTACT (gdata_parsable_new_from_xml (GDATA_TYPE_CONTACTS_CONTACT,
		"<entry xmlns='http://www.w3.org/2005/Atom' "
			"xmlns:gd='http://schemas.google.com/g/2005'>"
			"<id>http://www.google.com/m8/feeds/contacts/libgdata.test@googlemail.com/base/1b46cdd20bfbee3b</id>"
			"<updated>2009-04-25T15:21:53.688Z</updated>"
			"<category scheme='http://schemas.google.com/g/2005#kind' term='http://schemas.google.com/contact/2008#contact'/>"
			"<title></title>"
			"<link rel='http://schemas.google.com/contacts/2008/rel#photo' type='image/*' "
			      "href='http://www.google.com/m8/feeds/photos/media/libgdata.test@googlemail.com/1b46cdd20bfbee3b'/>"
		"</entry>", -1, &error));
	g_assert_no_error (error);
	g_assert (GDATA_IS_CONTACTS_CONTACT (contact));
	gdata_test_compare_kind (GDATA_ENTRY (contact), "http://schemas.google.com/contact/2008#contact", NULL);
	g_clear_error (&error);


	g_assert (gdata_contacts_contact_get_photo_etag (contact) == NULL);
	g_assert (gdata_contacts_contact_get_photo (contact, GDATA_CONTACTS_SERVICE (service), &length, &content_type, NULL, &error) == NULL);
	g_assert_cmpint (length, ==, 0);
	g_assert (content_type == NULL);
	g_assert_no_error (error);

	g_clear_error (&error);
	g_free (content_type);
	g_object_unref (contact);


	contact = GDATA_CONTACTS_CONTACT (gdata_parsable_new_from_xml (GDATA_TYPE_CONTACTS_CONTACT,
		"<entry xmlns='http://www.w3.org/2005/Atom' "
			"xmlns:gd='http://schemas.google.com/g/2005'>"
			"<id>http://www.google.com/m8/feeds/contacts/libgdata.test@googlemail.com/base/1b46cdd20bfbee3b</id>"
			"<updated>2009-04-25T15:21:53.688Z</updated>"
			"<category scheme='http://schemas.google.com/g/2005#kind' term='http://schemas.google.com/contact/2008#contact'/>"
			"<title></title>"
			"<link rel='http://schemas.google.com/contacts/2008/rel#photo' type='image/*' "
			      "href='http://www.google.com/m8/feeds/photos/media/libgdata.test@googlemail.com/1b46cdd20bfbee3b' "
			     "gd:etag='&quot;QngzcDVSLyp7ImA9WxJTFkoITgU.&quot;'/>"
		"</entry>", -1, &error));
	g_assert_no_error (error);
	g_assert (GDATA_IS_CONTACTS_CONTACT (contact));
	gdata_test_compare_kind (GDATA_ENTRY (contact), "http://schemas.google.com/contact/2008#contact", NULL);
	g_clear_error (&error);

	g_assert (gdata_contacts_contact_get_photo_etag (contact) != NULL);
	g_object_unref (contact);
}
