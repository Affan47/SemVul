test_list_insert_before ()
{
	GList *foo, *bar, *baz;

	foo = g_list_prepend (NULL, "foo");
	foo = g_list_insert_before (foo, NULL, "bar");
	bar = g_list_last (foo);

	if (strcmp (bar->data, "bar"))
		return FAILED ("1");

	baz = g_list_insert_before (foo, bar, "baz");
	if (foo != baz)
		return FAILED ("2");

	if (strcmp (g_list_nth_data (foo, 1), "baz"))
		return FAILED ("3: %s", g_list_nth_data (foo, 1));

	g_list_free (foo);
	return OK;
}
