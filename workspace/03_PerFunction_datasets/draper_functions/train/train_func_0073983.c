test_object_property (Test *test, gconstpointer unused)
{
	GkmCredential *auth;
	GkmObject *check;
	CK_RV rv;

	rv = gkm_credential_create (test->module, NULL, test->object, (guchar*)"mock", 4, &auth);
	g_assert (rv == CKR_OK);
	g_assert (auth);

	g_object_get (auth, "object", &check, NULL);
	g_assert (check == test->object);
	g_object_unref (check);

	check = gkm_credential_get_object (auth);
	g_assert (check == test->object);

	g_object_unref (auth);
}
