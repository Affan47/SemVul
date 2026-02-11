e_table_header_get_columns (ETableHeader *eth)
{
	ETableCol **ret;
	gint i;

	g_return_val_if_fail (eth != NULL, NULL);
	g_return_val_if_fail (E_IS_TABLE_HEADER (eth), NULL);

	ret = g_new (ETableCol *, eth->col_count + 1);
	memcpy (ret, eth->columns, sizeof (ETableCol *) * eth->col_count);
	ret[eth->col_count] = NULL;

	for (i = 0; i < eth->col_count; i++) {
		g_object_ref (ret[i]);
	}

	return ret;
}
