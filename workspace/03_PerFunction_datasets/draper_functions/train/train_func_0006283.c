sheet_set_display_formulas (Sheet *sheet, gboolean display)
{
	display = !!display;
	if (sheet->display_formulas == display)
		return;

	sheet->display_formulas = display;
	sheet_mark_dirty (sheet);
	if (!sheet->being_constructed)
		sheet_scale_changed (sheet, TRUE, FALSE);
}
