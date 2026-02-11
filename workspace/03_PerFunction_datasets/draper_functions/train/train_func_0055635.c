filter_load_file_type(const gchar **attribute_names, const gchar **attribute_values)
{
	FilterEntry fe;
	FilterEntry *old_fe;
	memset(&fe, 0, sizeof(fe));
	while (*attribute_names)
		{
		const gchar *option = *attribute_names++;
		const gchar *value = *attribute_values++;

		if (READ_CHAR(fe, key)) continue;
		if (READ_BOOL(fe, enabled)) continue;
		if (READ_CHAR(fe, extensions)) continue;
		if (READ_CHAR(fe, description)) continue;
		if (READ_UINT(fe, file_class)) continue;
		if (READ_BOOL(fe, writable)) continue;
		if (READ_BOOL(fe, allow_sidecar)) continue;

		log_printf("unknown attribute %s = %s\n", option, value);
		}
	if (fe.file_class >= FILE_FORMAT_CLASSES) fe.file_class = FORMAT_CLASS_UNKNOWN;

	if (fe.key && fe.key[0] != 0)
		{
		old_fe = filter_get_by_key(fe.key);

		if (old_fe != NULL) filter_remove_entry(old_fe);
		filter_add(fe.key, fe.description, fe.extensions, fe.file_class, fe.writable, fe.allow_sidecar, fe.enabled);
		}
	g_free(fe.key);
	g_free(fe.extensions);
	g_free(fe.description);
}
