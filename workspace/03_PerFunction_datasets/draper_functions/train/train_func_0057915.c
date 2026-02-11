sheet_set_zoom_factor (Sheet *sheet, double factor)
{
	if (fabs (factor - sheet->last_zoom_factor_used) < 1e-6)
		return;
	sheet->last_zoom_factor_used = factor;
	if (!sheet->being_constructed)
		sheet_scale_changed (sheet, TRUE, TRUE);
}
