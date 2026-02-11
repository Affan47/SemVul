odf_apply_ooo_table_config (char const *key, GValue *val, OOParseState *state)
{
	if (G_VALUE_HOLDS(val,G_TYPE_HASH_TABLE)) {
		GHashTable *hash = g_value_get_boxed (val);
		Sheet *sheet = workbook_sheet_by_name (state->pos.wb, key);
		if (hash != NULL && sheet != NULL) {
			GValue *item = g_hash_table_lookup (hash, "TabColor");
			if (item != NULL && G_VALUE_HOLDS(item, G_TYPE_INT)) {
				GOColor color = g_value_get_int (item);
				color = color << 8;
				sheet->tab_color = gnm_color_new_go (color);
			}
			item = g_hash_table_lookup (hash, "CursorPositionX");
			if (item != NULL && G_VALUE_HOLDS(item, G_TYPE_INT)) {
				GValue *itemy = g_hash_table_lookup (hash, "CursorPositionY");
				if (itemy != NULL && G_VALUE_HOLDS(itemy, G_TYPE_INT)) {
					GnmCellPos pos;
					SheetView *sv
						= sheet_get_view (sheet, state->wb_view);
					GnmRange r;
					pos.col = g_value_get_int (item);
					pos.row = g_value_get_int (itemy);
					r.start = pos;
					r.end = pos;

					sv_selection_reset (sv);
					sv_selection_add_range (sv, &r);
					sv_set_edit_pos
						(sheet_get_view (sheet, state->wb_view),
						 &pos);
				}
			}
		}
	}
}
