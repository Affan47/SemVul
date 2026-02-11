test_attribute_match (Test *test, gconstpointer unused)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GckUriData *uri_data;
	GError *error = NULL;
	GckEnumerator *en;
	GList *objects;

	uri_data = gck_uri_data_new ();
	gck_builder_add_string (&builder, CKA_LABEL, "Private Capitalize Key");
	uri_data->attributes = gck_attributes_ref_sink (gck_builder_end (&builder));
	en = _gck_enumerator_new_for_modules (test->modules, 0, uri_data);
	g_assert (GCK_IS_ENUMERATOR (en));

	objects = gck_enumerator_next_n (en, -1, NULL, &error);
	g_assert_no_error (error);
	g_assert_cmpint (g_list_length (objects), ==, 1);
	g_assert (GCK_IS_OBJECT (objects->data));

	gck_list_unref_free (objects);
	g_object_unref (en);
}
