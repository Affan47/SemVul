setup_book (EBookClient *book_client)
{
	if (!add_contact_from_test_case_verify (book_client, "simple-1", NULL) ||
	    !add_contact_from_test_case_verify (book_client, "simple-2", NULL) ||
	    !add_contact_from_test_case_verify (book_client, "name-only", NULL)) {
		g_error ("Failed to add contacts");
	}
}
