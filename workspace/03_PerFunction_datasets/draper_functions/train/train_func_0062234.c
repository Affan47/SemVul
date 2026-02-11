test_is_pinned_none (Test *test, gconstpointer unused)
{
	GError *error = NULL;
	gboolean trust;

	trust = gcr_trust_is_certificate_pinned (test->certificate, GCR_PURPOSE_EMAIL, "host", NULL, &error);
	g_assert_cmpint (trust, ==, FALSE);
	g_assert (error == NULL);
}
