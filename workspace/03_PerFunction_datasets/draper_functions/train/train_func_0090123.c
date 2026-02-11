ebook_test_utils_book_commit_contact (EBook *book,
                                      EContact *contact)
{
	GError *error = NULL;

	if (!e_book_commit_contact (book, contact, &error)) {
		ESource *source;
		const gchar *name;
		const gchar *uid;

		uid = (const gchar *) e_contact_get_const (contact, E_CONTACT_UID);

		source = e_book_get_source (book);
		name = e_source_get_display_name (source);
		g_warning (
			"failed to commit changes to contact '%s' to "
			"addressbook: `%s': %s", uid, name, error->message);
		exit (1);
	}
}
