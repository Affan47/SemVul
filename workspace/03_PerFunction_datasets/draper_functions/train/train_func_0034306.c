mono_metadata_decode_table_row_col (MonoImage *image, int table, int idx, guint col)
{
	if (image->uncompressed_metadata)
		idx = mono_metadata_translate_token_index (image, table, idx + 1) - 1;

	return mono_metadata_decode_row_col (&image->tables [table], idx, col);
}
