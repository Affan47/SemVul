mono_metadata_decode_table_row (MonoImage *image, int table, int idx, guint32 *res, int res_size)
{
	if (image->uncompressed_metadata)
		idx = mono_metadata_translate_token_index (image, table, idx + 1) - 1;

	mono_metadata_decode_row (&image->tables [table], idx, res, res_size);
}
