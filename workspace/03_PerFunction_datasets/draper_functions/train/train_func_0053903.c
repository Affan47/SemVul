test_iter_remove_all (void)
{
	GMimeHeaderList *list;
	GMimeHeaderIter iter;
	guint i = 0;

	list = header_list_new ();

	g_mime_header_list_get_iter (list, &iter);

	testsuite_check ("removing all headers");
	try {
		while (g_mime_header_iter_remove (&iter))
			i++;

		if (i != G_N_ELEMENTS (initial))
			throw (exception_new ("only removed %u of %u", i, G_N_ELEMENTS (initial)));

		if (g_mime_header_iter_is_valid (&iter))
			throw (exception_new ("expected invalid iter"));

		testsuite_check_passed ();
	} catch (ex) {
		testsuite_check_failed ("removing all headers: %s", ex->message);
	} finally;

	g_mime_header_list_get_iter (list, &iter);

	testsuite_check ("empty list iter");
	try {
		if (g_mime_header_iter_is_valid (&iter))
			throw (exception_new ("expected invalid iter"));

		testsuite_check_passed ();
	} catch (ex) {
		testsuite_check_failed ("empty list iter: %s", ex->message);
	} finally;

	g_mime_header_list_destroy (list);
}
