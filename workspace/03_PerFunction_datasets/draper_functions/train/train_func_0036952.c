dump_table_exported (MonoImage *m)
{
	MonoTableInfo *t = &m->tables [MONO_TABLE_EXPORTEDTYPE];
	guint32 cols [MONO_EXP_TYPE_SIZE];
	int i;
	const char *name, *nspace;
	char *impl;
	guint32 index, flags;
	fprintf (output, "ExportedType Table (1..%d)\n", t->rows);

	for (i = 1; i <= t->rows; i++) {
		mono_metadata_decode_row (t, i - 1, cols, MONO_EXP_TYPE_SIZE);
		name = mono_metadata_string_heap (m, cols [MONO_EXP_TYPE_NAME]);
		nspace = mono_metadata_string_heap (m, cols [MONO_EXP_TYPE_NAMESPACE]);
		impl = get_manifest_implementation (m, cols [MONO_EXP_TYPE_IMPLEMENTATION]);
		index = cols [MONO_EXP_TYPE_TYPEDEF];
		flags = cols [MONO_EXP_TYPE_FLAGS];
		fprintf (output, "%d: %s%s%s is in %s, index=%x, flags=0x%x\n", i, nspace, *nspace ? "." : "", name, impl, index, flags);
		g_free (impl);
	}

}
