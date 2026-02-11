string_entry_new(const gchar *str)
{
	StringEntry *entry;

	entry = g_new0(StringEntry, 1);
	entry->ref_count = 1;
	entry->string = g_strdup(str);
	return entry;
}
