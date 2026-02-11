test_get_compat_hashed_string (void)
{
	GHashTable *fields;
	gboolean ret;
	gchar *value;

	fields = gkm_secret_fields_new ();
	gkm_secret_fields_add (fields, "test", "value");

	ret = gkm_secret_fields_get_compat_hashed_string (fields, "test", &value);
	g_assert (ret == TRUE);
	g_assert_cmpstr (value, ==, "2063c1608d6e0baf80249c42e2be5804");
	g_free (value);

	g_hash_table_unref (fields);
}
