ebook_test_utils_book_add_contact (EBook *book,
                                   EContact *contact)
{
	GError *error = NULL;

	if (!e_book_add_contact (book, contact, &error)) {
		ESource *source;
		const gchar *name;

		source = e_book_get_source (book);
		name = e_source_get_display_name (source);
		g_warning (
			"failed to add contact to addressbook: `%s': %s",
			name, error->message);
		exit (1);
	}

	return e_contact_get_const (contact, E_CONTACT_UID);
}
