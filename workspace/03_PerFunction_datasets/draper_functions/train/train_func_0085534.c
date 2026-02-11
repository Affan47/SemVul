test_defname_no_conflict (void)
{
	GHashTable *hash;
	char *name;

	hash = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, (GDestroyNotify) g_object_unref);

	g_hash_table_insert (hash, "a", _new_connection ("asdfasdfasdfadf"));
	g_hash_table_insert (hash, "b", _new_connection ("work wifi"));
	g_hash_table_insert (hash, "c", _new_connection ("random gsm connection"));

	name = nm_settings_utils_get_default_wired_name (hash);
	g_assert_cmpstr (name, ==, "Wired connection 1");

	g_hash_table_destroy (hash);
}
