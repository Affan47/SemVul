test_truncate ()
{
	GString *s = g_string_new ("0123456789");
	g_string_truncate (s, 3);

	if (strlen (s->str) != 3)
		return FAILED ("size of string should have been 3, instead it is [%s]\n", s->str);
	g_string_free (s, TRUE);

	s = g_string_new ("a");
	s = g_string_truncate (s, 10);
	if (strlen (s->str) != 1)
		return FAILED ("The size is not 1");
	g_string_truncate (s, (gsize)-1);
	if (strlen (s->str) != 1)
		return FAILED ("The size is not 1");
	g_string_truncate (s, 0);
	if (strlen (s->str) != 0)
		return FAILED ("The size is not 0");

	g_string_free (s, TRUE);

	return NULL;
}
