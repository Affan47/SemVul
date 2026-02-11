e_book_remove (EBook *book,
               GError **error)
{
	ESource *source;
	g_return_val_if_fail (E_IS_BOOK (book), FALSE);

	source = e_book_get_source (book);

	return e_source_remove_sync (source, NULL, error);
}
