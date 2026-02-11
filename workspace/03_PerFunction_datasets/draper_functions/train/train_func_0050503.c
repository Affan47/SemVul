test_keyid_for_records (Test *test, gconstpointer unused)
{
	const gchar *keyid;

	keyid = _gcr_gnupg_records_get_keyid (test->records);
	g_assert_cmpstr (keyid, ==, "6C7EE1B8621CC013");
}
