dump_table_interfaceimpl (MonoImage *m)
{
	MonoTableInfo *t = &m->tables [MONO_TABLE_INTERFACEIMPL];
	int i;

	fprintf (output, "Interface Implementation Table (1..%d)\n", t->rows);
	for (i = 1; i <= t->rows; i++) {
		guint32 cols [MONO_INTERFACEIMPL_SIZE];

		mono_metadata_decode_row (t, i - 1, cols, MONO_INTERFACEIMPL_SIZE);
		fprintf (output, "%d: %s implements %s\n", i,
			 get_typedef (m, cols [MONO_INTERFACEIMPL_CLASS]),
			 get_typedef_or_ref (m, cols [MONO_INTERFACEIMPL_INTERFACE], NULL));
	}
}
