dump_table_field_marshal (MonoImage *m)
{
	MonoTableInfo *t = &m->tables [MONO_TABLE_FIELDMARSHAL];
	guint32 cols [MONO_FIELD_MARSHAL_SIZE];
	int i, is_field, idx;
	const char *blob;
	char *native;

	fprintf (output, "FieldMarshal Table (1..%d)\n", t->rows);

	for (i = 1; i <= t->rows; i++) {
		mono_metadata_decode_row (t, i - 1, cols, MONO_FIELD_MARSHAL_SIZE);
		blob = mono_metadata_blob_heap (m, cols [MONO_FIELD_MARSHAL_NATIVE_TYPE]);
		native = get_marshal_info (m, blob);
		is_field = (cols [MONO_FIELD_MARSHAL_PARENT] & MONO_HAS_FIELD_MARSHAL_MASK) == MONO_HAS_FIELD_MARSHAL_FIELDSREF;
		idx = cols [MONO_FIELD_MARSHAL_PARENT] >> MONO_HAS_FIELD_MARSHAL_BITS;
		fprintf (output, "%d: (0x%04x) %s %d: %s\n", i, cols [MONO_FIELD_MARSHAL_PARENT], is_field? "Field" : "Param", idx, native);
		fprintf (output, "\tblob encoding: ");
		dump_blob (m, blob);
		fprintf (output, "\n");
		g_free (native);
	}

}
