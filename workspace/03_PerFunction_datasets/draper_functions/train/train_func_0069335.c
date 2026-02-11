test_find_objects (Test *test, gconstpointer unused)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GAsyncResult *result = NULL;
	GList *objects;
	GckObject *testobj;
	GError *err = NULL;

	gck_builder_add_ulong (&builder, CKA_CLASS, CKO_DATA);
	gck_builder_add_string (&builder, CKA_LABEL, "UNIQUE LABEL");
	testobj = gck_session_create_object (test->session, gck_builder_end (&builder), NULL, &err);
	g_object_unref (testobj);

	gck_builder_add_ulong (&builder, CKA_CLASS, CKO_DATA);
	gck_builder_add_string (&builder, CKA_LABEL, "OTHER LABEL");
	testobj = gck_session_create_object (test->session, gck_builder_end (&builder), NULL, &err);
	g_object_unref (testobj);


	gck_builder_add_string (&builder, CKA_LABEL, "UNIQUE LABEL");
	objects = gck_session_find_objects (test->session, gck_builder_end (&builder), NULL, &err);
	g_assert_no_error (err);
	g_assert (g_list_length (objects) == 1);
	gck_list_unref_free (objects);


	objects = gck_session_find_objects (test->session, gck_builder_end (&builder), NULL, &err);
	g_assert_no_error (err);
	g_assert (g_list_length (objects) > 1);
	gck_list_unref_free (objects);


	gck_builder_add_string (&builder, CKA_LABEL, "blah blah");
	gck_session_find_objects_async (test->session, gck_builder_end (&builder), NULL, fetch_async_result, &result);
	egg_test_wait_until (500);
	g_assert (result != NULL);

	objects = gck_session_find_objects_finish (test->session, result, &err);
	g_object_unref (result);
	g_assert (objects == NULL);
	gck_list_unref_free (objects);
}
