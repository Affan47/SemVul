on_collection_added (GcrCollection *collection, GObject *object, gpointer user_data)
{
	Test *test = user_data;
	GcrGnupgKey *key;
	const gchar *keyid;

	g_assert (GCR_COLLECTION (test->collection) == collection);

	g_assert (GCR_IS_GNUPG_KEY (object));
	key = GCR_GNUPG_KEY (object);

	keyid = _gcr_gnupg_key_get_keyid (key);
	g_assert (keyid);
	g_assert (!g_hash_table_lookup (test->keys, keyid));

	g_hash_table_insert (test->keys, g_strdup (keyid), key);
}
