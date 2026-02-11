dump_table_property (MonoImage *m)
{
	MonoTableInfo *t = &m->tables [MONO_TABLE_PROPERTY];
	int i, j, pcount;
	const char *ptr;
	char flags[128];

	fprintf (output, "Property Table (1..%d)\n", t->rows);

	for (i = 0; i < t->rows; i++){
		guint32 cols [MONO_PROPERTY_SIZE];
		char *type;
		int bsize;
		int prop_flags;

		mono_metadata_decode_row (t, i, cols, MONO_PROPERTY_SIZE);
		flags [0] = 0;
		prop_flags = cols [MONO_PROPERTY_FLAGS];
		if (prop_flags & 0x0200)
			strcat (flags, "special ");
		if (prop_flags & 0x0400)
			strcat (flags, "runtime ");
		if (prop_flags & 0x1000)
			strcat (flags, "hasdefault ");

		ptr = mono_metadata_blob_heap (m, cols [MONO_PROPERTY_TYPE]);
		bsize = mono_metadata_decode_blob_size (ptr, &ptr);

		if (*ptr != 0x28 && *ptr != 0x08)
			g_warning("incorrect signature in propert blob: 0x%x", *ptr);
		ptr++;
		pcount = mono_metadata_decode_value (ptr, &ptr);
		ptr = get_type (m, ptr, &type, FALSE, NULL);
		fprintf (output, "%d: %s %s (",
			 i + 1, type, mono_metadata_string_heap (m, cols [MONO_PROPERTY_NAME]));
		g_free (type);

		for (j = 0; j < pcount; j++){
			ptr = get_param (m, ptr, &type, NULL);
			fprintf (output, "%s%s", j > 0? ", " : "",type);
			g_free (type);
		}
		fprintf (output, ") %s\n", flags);
	}
}
