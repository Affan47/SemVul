print_page_col_headers (GtkPrintContext   *context,
			G_GNUC_UNUSED PrintingInstance * pi,
			cairo_t *cr, Sheet const *sheet, GnmRange *range,
			double row_header_width, double col_header_height)
{
	int start_col, end_col;
	int col;
	double x;
	PangoFontDescription *desc;
	double hscale;

	g_return_if_fail (IS_SHEET (sheet));
	g_return_if_fail (range != NULL);
	g_return_if_fail (range->start.col <= range->end.col);

	hscale = sheet->display_formulas ? 2 : 1;
	desc = pango_font_description_from_string ("sans 12");

	start_col = range->start.col;
	end_col = range->end.col;

	x = (row_header_width + GNM_COL_MARGIN) * (sheet->text_is_rtl ? -1. : 1.);

	for (col = start_col; col <= end_col ; col++) {
		ColRowInfo const *ci = sheet_col_get_info (sheet, col);

		if (ci->visible) {
			if (sheet->text_is_rtl)
				x -= ci->size_pts * hscale;

			print_header_gtk (context, cr,
					  x + 0.5, 0,
					  ci->size_pts * hscale - 1,
					  col_header_height - 0.5,
					  col_name (col), desc);

			if (!sheet->text_is_rtl)
				x += ci->size_pts * hscale;
		}
	}

	pango_font_description_free (desc);
}
