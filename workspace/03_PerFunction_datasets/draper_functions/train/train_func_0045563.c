ebook_test_utils_book_remove_contact (EBook *book,
                                      const gchar *uid)
{
	GError *error = NULL;

	if (!e_book_remove_contact (book, uid, &error)) {
		ESource *source;
		const gchar *name;

		source = e_book_get_source (book);
		name = e_source_get_display_name (source);
		g_warning (
			"failed to remove contact '%s' from addressbook: "
			"`%s': %s", uid, name, error->message);
		exit (1);
	}
}
