dump_table_param (MonoImage *m)
{
	MonoTableInfo *t = &m->tables [MONO_TABLE_PARAM];
	int i;

	fprintf (output, "Param Table\n");

	for (i = 0; i < t->rows; i++){
		guint32 cols [MONO_PARAM_SIZE];

		mono_metadata_decode_row (t, i, cols, MONO_PARAM_SIZE);
		fprintf (output, "%d: 0x%04x %d %s\n",
			 i + 1,
			 cols [MONO_PARAM_FLAGS], cols [MONO_PARAM_SEQUENCE],
			 mono_metadata_string_heap (m, cols [MONO_PARAM_NAME]));
	}
	fprintf (output, "\n");
}
