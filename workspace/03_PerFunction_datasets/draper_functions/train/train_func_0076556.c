test_add_and_remov_pinned_async (Test *test, gconstpointer unused)
{
	GAsyncResult *result = NULL;
	GError *error = NULL;
	gboolean trust;
	gboolean ret;

	gcr_trust_add_pinned_certificate_async (test->certificate, GCR_PURPOSE_EMAIL, "host", NULL, fetch_async_result, &result);
	egg_test_wait_until (500);
	g_assert (result);
	ret = gcr_trust_add_pinned_certificate_finish (result, &error);
	g_assert (ret == TRUE);
	g_assert (error == NULL);
	g_object_unref (result);
	result = NULL;

	gcr_trust_is_certificate_pinned_async (test->certificate, GCR_PURPOSE_EMAIL, "host", NULL, fetch_async_result, &result);
	egg_test_wait_until (500);
	g_assert (result);
	trust = gcr_trust_is_certificate_pinned_finish (result, &error);
	g_assert (trust == TRUE);
	g_assert (error == NULL);
	g_object_unref (result);
	result = NULL;

	gcr_trust_remove_pinned_certificate_async (test->certificate, GCR_PURPOSE_EMAIL, "host", NULL, fetch_async_result, &result);
	egg_test_wait_until (500);
	g_assert (result);
	ret = gcr_trust_remove_pinned_certificate_finish (result, &error);
	g_assert (ret == TRUE);
	g_assert (error == NULL);
	g_object_unref (result);
	result = NULL;

	gcr_trust_is_certificate_pinned_async (test->certificate, GCR_PURPOSE_EMAIL, "host", NULL, fetch_async_result, &result);
	egg_test_wait_until (500);
	g_assert (result);
	trust = gcr_trust_is_certificate_pinned_finish (result, &error);
	g_assert (trust == FALSE);
	g_assert (error == NULL);
	g_object_unref (result);
	result = NULL;
}
