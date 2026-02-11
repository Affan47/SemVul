test_get_base64 (Test *test, gconstpointer unused)
{
	gchar *value;
	gsize n_value;

	value = _gcr_record_get_base64 (test->record, 3, &n_value);
	g_assert (value);
	egg_assert_cmpsize (n_value, ==, 8);
	g_assert (memcmp (value, "aoeu3838", n_value) == 0);

	g_free (value);
}
