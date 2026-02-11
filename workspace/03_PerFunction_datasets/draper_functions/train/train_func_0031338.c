test_delete_sync (Test *test,
                  gconstpointer used)
{
	GError *error = NULL;
	gboolean ret;

	ret = secret_password_clear_sync (&MOCK_SCHEMA, NULL, &error,
	                                  "even", FALSE,
	                                  "string", "one",
	                                  "number", 1,
	                                  NULL);

	g_assert_no_error (error);
	g_assert (ret == TRUE);
}
