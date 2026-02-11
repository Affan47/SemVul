odf_save_this_style (G_GNUC_UNUSED gconstpointer dummy, GnmStyleRegion *sr, GnmOOExport *state)
{
	char *name;
	GnmStyleConditions const *sc;

	if (NULL != g_hash_table_lookup (state->cell_styles, sr->style))
		return;

	name = g_strdup_printf ("ACE-%p", sr->style);
	g_hash_table_insert (state->cell_styles, sr->style, name);

	if (gnm_style_is_element_set (sr->style, MSTYLE_CONDITIONS) &&
	    NULL != (sc = gnm_style_get_conditions (sr->style))) {
		GPtrArray const *conds = gnm_style_conditions_details (sc);
		if (conds != NULL) {
			guint i;
			for (i = 0 ; i < conds->len ; i++) {
				GnmStyleCond const *cond =
					g_ptr_array_index (conds, i);
				odf_store_this_named_style (cond->overlay, NULL, &sr->range, state);
			}
		}
	}

	odf_save_this_style_with_name (sr, name, state);
}
