test_verify (Test *test, gconstpointer unused)
{
	GckMechanism mech = { CKM_MOCK_PREFIX, (guchar *)"my-prefix:", 10 };
	GError *error = NULL;
	GAsyncResult *result = NULL;
	GckObject *key;
	gboolean ret;


	g_signal_connect (test->module, "authenticate-object", G_CALLBACK (authenticate_object), NULL);


	key = find_key (test->session, CKA_VERIFY, CKM_MOCK_PREFIX);
	g_assert (GCK_IS_OBJECT (key));
	g_object_add_weak_pointer (G_OBJECT (key), (gpointer *)&key);


	ret = gck_session_verify (test->session, key, CKM_MOCK_PREFIX, (const guchar*)"Labarbara", 10,
	                           (const guchar*)"signed-prefix:Labarbara", 24, NULL, &error);
	g_assert_no_error (error);
	g_assert (ret);


	ret = gck_session_verify_full (test->session, key, &mech, (const guchar*)"Labarbara", 10,
	                                (const guchar*)"my-prefix:Loborboro", 20, NULL, &error);
	g_assert (error != NULL);
	g_assert (!ret);
	g_clear_error (&error);


	gck_session_verify_async (test->session, key, &mech, (const guchar*)"Labarbara", 10,
	                           (const guchar*)"my-prefix:Labarbara", 20, NULL, fetch_async_result, &result);
	egg_test_wait_until (500);
	g_assert (result != NULL);
	ret = gck_session_verify_finish (test->session, result, &error);
	g_assert_no_error (error);
	g_assert (ret);
	g_object_unref (result);


	result = NULL;
	gck_session_verify_async (test->session, key, &mech, (const guchar*)"Labarbara", 10,
	                           (const guchar*)"my-prefix:Labarxoro", 20, NULL, fetch_async_result, &result);
	egg_test_wait_until (500);
	g_assert (result != NULL);
	ret = gck_session_verify_finish (test->session, result, &error);
	g_assert (error != NULL);
	g_assert (!ret);
	g_clear_error (&error);
	g_object_unref (result);

	g_object_unref (key);
	g_assert (key == NULL);
}
