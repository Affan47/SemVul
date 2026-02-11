ebook_test_utils_book_async_get_supported_auth_methods (EBook *book,
                                                        GSourceFunc callback,
                                                        gpointer user_data)
{
	EBookTestClosure *closure;

	closure = g_new0 (EBookTestClosure, 1);
	closure->cb = callback;
	closure->user_data = user_data;
	if (!e_book_get_supported_auth_methods_async (book,
				(EBookEListAsyncCallback) get_supported_auth_methods_cb,
				closure)) {
		g_warning ("failed to set up async getSupportedAuthMethods");
		exit (1);
	}
}
