test_validate_schema (void)
{
	GHashTable *attributes;
	gboolean ret;

	attributes = g_hash_table_new (g_str_hash, g_str_equal);
	g_hash_table_replace (attributes, "number", "1");
	g_hash_table_replace (attributes, "string", "test");
	g_hash_table_replace (attributes, "xdg:schema", "org.mock.Schema");

	ret = _secret_attributes_validate (&MOCK_SCHEMA, attributes, G_STRFUNC, TRUE);
	g_assert (ret == TRUE);

	g_hash_table_unref (attributes);
}
