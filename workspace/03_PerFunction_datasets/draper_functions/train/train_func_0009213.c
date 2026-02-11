setup (Test *test,
       gconstpointer unused)
{
	GkmDataResult res;

	test->module = test_secret_module_initialize_and_enter ();
	test->session = test_secret_module_open_session (TRUE);

	test->collection = g_object_new (GKM_TYPE_SECRET_COLLECTION,
	                                 "module", test->module,
	                                 "manager", gkm_session_get_manager (test->session),
	                                 "identifier", "test-collection",
	                                 NULL);


	gkm_secret_collection_set_filename (test->collection,
	                                    SRCDIR "/files/schema1.keyring");


	res = gkm_secret_collection_load (test->collection);
	g_assert (res == GKM_DATA_SUCCESS);
	gkm_object_expose (GKM_OBJECT (test->collection), TRUE);
}
