gnm_sheet_merge_is_corner (Sheet const *sheet, GnmCellPos const *pos)
{
	g_return_val_if_fail (IS_SHEET (sheet), NULL);
	g_return_val_if_fail (pos != NULL, NULL);

	return g_hash_table_lookup (sheet->hash_merged, pos);
}
