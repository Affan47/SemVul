standard_is_strings (const char *key)
{
	static GHashTable *strings = NULL;

	if (strings == NULL) {
		strings = g_hash_table_new (g_str_hash, g_str_equal);
		g_hash_table_insert (strings,
				     GNOME_DESKTOP_ITEM_FILE_PATTERN,
				     GNOME_DESKTOP_ITEM_FILE_PATTERN);
		g_hash_table_insert (strings,
				     GNOME_DESKTOP_ITEM_ACTIONS,
				     GNOME_DESKTOP_ITEM_ACTIONS);
		g_hash_table_insert (strings,
				     GNOME_DESKTOP_ITEM_MIME_TYPE,
				     GNOME_DESKTOP_ITEM_MIME_TYPE);
		g_hash_table_insert (strings,
				     GNOME_DESKTOP_ITEM_PATTERNS,
				     GNOME_DESKTOP_ITEM_PATTERNS);
		g_hash_table_insert (strings,
				     GNOME_DESKTOP_ITEM_SORT_ORDER,
				     GNOME_DESKTOP_ITEM_SORT_ORDER);
	}

	return g_hash_table_lookup (strings, key) != NULL;
}
