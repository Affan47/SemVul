dump_section (GnomeDesktopItem *item, GFileOutputStream *stream, Section *section)
{
	GList *li;

	stream_printf (stream, "[%s]\n", section->name);
	for (li = section->keys; li != NULL; li = li->next) {
		const char *key = li->data;
		char *full = g_strdup_printf ("%s/%s", section->name, key);
		const char *value = g_hash_table_lookup (item->main_hash, full);
		if (value != NULL) {
			char *val = escape_string_and_dup (value);
			stream_printf (stream, "%s=%s\n", key, val);
			g_free (val);
		}
		g_free (full);
	}
}
