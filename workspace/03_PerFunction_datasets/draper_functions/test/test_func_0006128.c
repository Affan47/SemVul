excel_write_prep_expressions (ExcelWriteState *ewb)
{
	g_return_if_fail (ewb != NULL);

	ewb->sheet_pairs = g_hash_table_new_full (
		(GHashFunc) sheet_pair_hash, (GEqualFunc) sheet_pair_cmp,
		NULL, g_free);
}
