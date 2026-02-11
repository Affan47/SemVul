lotus_set_style_cb (LotusState *state, const GnmSheetRange *r,
		    const guint8 *data, size_t len)
{
	guint sid;
	GnmStyle *style;

	g_return_if_fail (len == 0 || len == 2);
	if (len == 0)
		return;

	sid = GSF_LE_GET_GUINT16 (data);
#ifdef DEBUG_STYLE
	g_printerr ("Got style %d for %s!%s",
		 sid,
		 r->sheet->name_unquoted,
		 cellpos_as_string (&r->range.start));
	g_printerr (":%s\n",
		 cellpos_as_string (&r->range.end));
#endif

	style = g_hash_table_lookup (state->style_pool,
				     GUINT_TO_POINTER (sid));
	g_return_if_fail (style != NULL);

#ifdef DEBUG_STYLE
	gnm_style_dump (style);
#endif

	gnm_style_ref (style);
	sheet_apply_style (r->sheet, &r->range, style);
}
