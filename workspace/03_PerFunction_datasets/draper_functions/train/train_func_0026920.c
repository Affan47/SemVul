dump_table_constant (MonoImage *m)
{
	MonoTableInfo *t = &m->tables [MONO_TABLE_CONSTANT];
	int i;
	const char *desc [] = {
		"Field",
		"Param",
		"Property",
		""
	};
	fprintf (output, "Constant Table (1..%d)\n", t->rows);

	for (i = 0; i < t->rows; i++){
		guint32 cols [MONO_CONSTANT_SIZE];
		const char *parent;
		mono_metadata_decode_row (t, i, cols, MONO_CONSTANT_SIZE);
		parent = desc [cols [MONO_CONSTANT_PARENT] & MONO_HASCONSTANT_MASK];

		fprintf (output, "%d: Parent= %s: %d %s\n",
			 i + 1, parent, cols [MONO_CONSTANT_PARENT] >> MONO_HASCONSTANT_BITS,
			 get_constant (m, (MonoTypeEnum) cols [MONO_CONSTANT_TYPE], cols [MONO_CONSTANT_VALUE]));
	}

}
