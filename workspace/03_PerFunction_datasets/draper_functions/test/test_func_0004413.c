dis_data (MonoImage *m)
{
	MonoTableInfo *t = &m->tables [MONO_TABLE_FIELDRVA];
	MonoTableInfo *ft = &m->tables [MONO_TABLE_FIELD];
	int i, b;
	const char *rva, *sig;
	guint32 size;
	gint align;
	guint32 cols [MONO_FIELD_RVA_SIZE];
	MonoType *type;

	for (i = 0; i < t->rows; i++) {
		mono_metadata_decode_row (t, i, cols, MONO_FIELD_RVA_SIZE);
		rva = mono_image_rva_map (m, cols [MONO_FIELD_RVA_RVA]);
		sig = mono_metadata_blob_heap (m, mono_metadata_decode_row_col (ft, cols [MONO_FIELD_RVA_FIELD] -1, MONO_FIELD_SIGNATURE));
		mono_metadata_decode_value (sig, &sig);

		g_assert (*sig == 0x06);
		type = mono_metadata_parse_field_type (m, 0, sig + 1, &sig);
		mono_class_init (mono_class_from_mono_type (type));
		size = mono_type_size (type, &align);

		if (rva) {
			fprintf (output, ".data D_%08x = bytearray (", cols [MONO_FIELD_RVA_RVA]);
			for (b = 0; b < size; ++b) {
				if (!(b % 16))
					fprintf (output, "\n\t");
				fprintf (output, " %02X", rva [b] & 0xff);
			}
			fprintf (output, ") // size: %d\n", size);
		} else
			fprintf (output, ".data D_%08x = %s [%d]\n",
				cols [MONO_FIELD_RVA_RVA], get_uninitialized_data_type (size), size);
	}
}
