e_book_backend_get_direct_book (EBookBackend *backend)
{
	EBookBackendClass *class;
	EDataBookDirect *direct_book = NULL;

	g_return_val_if_fail (E_IS_BOOK_BACKEND (backend), NULL);

	class = E_BOOK_BACKEND_GET_CLASS (backend);

	if (class->get_direct_book != NULL)
		direct_book = class->get_direct_book (backend);

	return direct_book;
}
