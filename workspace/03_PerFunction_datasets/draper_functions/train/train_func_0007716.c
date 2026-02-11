test_factory_unnamed (Test *test, gconstpointer unused)
{
	CK_OBJECT_CLASS klass = CKO_G_COLLECTION;
	const gchar *identifier;
	GkmObject *object;

	CK_ATTRIBUTE attrs[] = {
		{ CKA_CLASS, &klass, sizeof (klass) },
		{ CKA_G_CREDENTIAL, &test->credential, sizeof (test->credential) },
	};

	object = gkm_session_create_object_for_factory (test->session, GKM_FACTORY_SECRET_COLLECTION, NULL,
	                                                attrs, G_N_ELEMENTS (attrs));
	g_assert (object != NULL);
	g_assert (GKM_IS_SECRET_COLLECTION (object));

	identifier = gkm_secret_object_get_identifier (GKM_SECRET_OBJECT (object));
	g_assert_cmpstr (identifier, !=, "");
	g_object_unref (object);
}
