test_add_and_remov_pinned (Test *test, gconstpointer unused)
{
	GError *error = NULL;
	gboolean trust;
	gboolean ret;

	ret = gcr_trust_add_pinned_certificate (test->certificate, GCR_PURPOSE_EMAIL, "host", NULL, &error);
	g_assert (ret == TRUE);
	g_assert (error == NULL);

	trust = gcr_trust_is_certificate_pinned (test->certificate, GCR_PURPOSE_EMAIL, "host", NULL, &error);
	g_assert_cmpint (trust, ==, TRUE);
	g_assert (error == NULL);

	ret = gcr_trust_remove_pinned_certificate (test->certificate, GCR_PURPOSE_EMAIL, "host", NULL, &error);
	g_assert (ret == TRUE);
	g_assert (error == NULL);

	trust = gcr_trust_is_certificate_pinned (test->certificate, GCR_PURPOSE_EMAIL, "host", NULL, &error);
	g_assert_cmpint (trust, ==, FALSE);
	g_assert (error == NULL);
}
