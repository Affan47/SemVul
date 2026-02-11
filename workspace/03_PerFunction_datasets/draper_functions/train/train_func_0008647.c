test_lookup_secret_no_match (Test *test, gconstpointer unused)
{
	gchar *password;

	password = gkm_wrap_login_lookup_secret ("invalid", "attribute",
	                                         "second", "attribute", NULL);
	g_assert_cmpstr (password, ==, NULL);
}
