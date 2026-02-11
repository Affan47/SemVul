test_session_initable (Test *test,
                       gconstpointer unused)
{
	GckSession *sess;
	GAsyncResult *result = NULL;
	GError *err = NULL;

	sess = gck_session_open (test->slot, 0, NULL, NULL, &err);
	g_assert_no_error (err);
	g_assert (GCK_IS_SESSION (sess));

	g_object_unref (sess);


	gck_session_open_async (test->slot, 0, NULL, NULL, fetch_async_result, &result);

	egg_test_wait_until (500);
	g_assert (result != NULL);


	sess = gck_session_open_finish (result, &err);
	g_assert_no_error (err);
	g_assert (GCK_IS_SESSION (sess));

	g_object_unref (result);
	g_object_unref (sess);
}
