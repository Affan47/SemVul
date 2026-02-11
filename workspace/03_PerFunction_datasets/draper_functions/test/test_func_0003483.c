sheet_style_get_row (Sheet const *sheet, GnmStyleRow *sr)
{

	g_return_if_fail (IS_SHEET (sheet));
	g_return_if_fail (sr != NULL);
	g_return_if_fail (sr->styles != NULL);
	g_return_if_fail (sr->vertical != NULL);
	g_return_if_fail (sr->top != NULL);
	g_return_if_fail (sr->bottom != NULL);

	sr->sheet = sheet;
	sr->vertical[sr->start_col] = gnm_style_border_none ();
	get_style_row (sheet->style_data->styles, sheet->tile_top_level, 0, 0, sr);
}
