test_next_and_resume (Test *test, gconstpointer unused)
{
	GckUriData *uri_data;
	GError *error = NULL;
	GckEnumerator *en;
	GckObject *obj, *obj2;

	uri_data = gck_uri_data_new ();
	en = _gck_enumerator_new_for_modules (test->modules, 0, uri_data);
	g_assert (GCK_IS_ENUMERATOR (en));

	obj = gck_enumerator_next (en, NULL, &error);
	g_assert_no_error (error);
	g_assert (GCK_IS_OBJECT (obj));

	obj2 = gck_enumerator_next (en, NULL, &error);
	g_assert_no_error (error);
	g_assert (GCK_IS_OBJECT (obj2));

	g_assert (!gck_object_equal (obj, obj2));

	g_object_unref (obj);
	g_object_unref (obj2);
	g_object_unref (en);
}
