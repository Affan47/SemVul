test_sign (Test *test, gconstpointer unused)
{
	GckMechanism mech = { CKM_MOCK_PREFIX, (guchar *)"my-prefix:", 10 };
	GError *error = NULL;
	GAsyncResult *result = NULL;
	GckObject *key;
	guchar *output;
	gsize n_output;


	g_signal_connect (test->module, "authenticate-object", G_CALLBACK (authenticate_object), NULL);


	key = find_key (test->session_with_auth, CKA_SIGN, CKM_MOCK_PREFIX);
	g_assert (key);


	output = gck_session_sign (test->session_with_auth, key, CKM_MOCK_PREFIX, (const guchar*)"Labarbara", 10, &n_output, NULL, &error);
	g_assert_no_error (error);
	g_assert (output);
	g_assert_cmpuint (n_output, ==, 24);
	g_assert_cmpstr ((gchar*)output, ==, "signed-prefix:Labarbara");
	g_free (output);


	gck_session_sign_async (test->session_with_auth, key, &mech, (const guchar*)"Conrad", 7, NULL, fetch_async_result, &result);

	egg_test_wait_until (500);
	g_assert (result != NULL);


	output = gck_session_sign_finish (test->session_with_auth, result, &n_output, &error);
	g_assert_no_error (error);
	g_assert (output);
	g_assert_cmpuint (n_output, ==, 17);
	g_assert_cmpstr ((gchar*)output, ==, "my-prefix:Conrad");
	g_free (output);

	g_object_unref (result);
	g_object_unref (key);
}
