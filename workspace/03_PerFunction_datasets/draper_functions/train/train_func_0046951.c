dis_directive_mresource (MonoImage *m)
{
	MonoTableInfo *t = &m->tables [MONO_TABLE_MANIFESTRESOURCE];
	int i;

	for (i = 0; i < t->rows; i++){
		guint32 cols [MONO_MANIFEST_SIZE];
		const char *name;
		guint32 impl, idx, name_token;

		mono_metadata_decode_row (t, i, cols, MONO_MANIFEST_SIZE);

		name = mono_metadata_string_heap (m, cols [MONO_MANIFEST_NAME]);

		fprintf (output, ".mresource %s '%s'\n", (cols [MONO_MANIFEST_FLAGS] & MANIFEST_RESOURCE_VISIBILITY_MASK) == (MANIFEST_RESOURCE_PUBLIC) ? "public" : "private", name);
		fprintf (output, "{\n");
		impl = cols [MONO_MANIFEST_IMPLEMENTATION];
		if (impl) {
			idx = impl >> MONO_IMPLEMENTATION_BITS;
			if ((impl & MONO_IMPLEMENTATION_MASK) == MONO_IMPLEMENTATION_FILE) {
				name_token = mono_metadata_decode_row_col (&m->tables [MONO_TABLE_FILE], idx - 1, MONO_FILE_NAME);

				fprintf (output, "    .file '%s' at 0x0\n", mono_metadata_string_heap (m, name_token));
			}
			if ((impl & MONO_IMPLEMENTATION_MASK) == MONO_IMPLEMENTATION_ASSEMBLYREF) {
				name_token = mono_metadata_decode_row_col (&m->tables [MONO_TABLE_ASSEMBLYREF], idx - 1, MONO_ASSEMBLYREF_NAME);
				fprintf (output, "    .assembly extern '%s'\n", mono_metadata_string_heap (m, name_token));
			}
		}
		fprintf (output, "}\n");
	}

}
