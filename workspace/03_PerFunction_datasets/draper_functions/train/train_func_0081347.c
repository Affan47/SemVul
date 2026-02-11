draw_dark_diagonal_hatch (cairo_surface_t *hatch, GpHatch *hbr)
{
	double hatch_size = gdip_hatch_get_width (hbr);

	cairo_t *ct2 = create_hatch_context (hatch, CAIRO_LINE_CAP_SQUARE, FALSE);
	if (ct2 == NULL)
		return CAIRO_STATUS_NO_MEMORY;

	draw_background (ct2, hbr->backColor, hatch_size, hatch_size);

	set_color (ct2, hbr->foreColor);
	if (hbr->hatchStyle == HatchStyleDarkDownwardDiagonal) {
		cairo_rectangle (ct2, 0, 0, 2, 1);
		cairo_rectangle (ct2, 1, 1, 2, 1);
		cairo_rectangle (ct2, 2, 2, 2, 1);
		cairo_rectangle (ct2, 0, 3, 1, 1);
		cairo_rectangle (ct2, 3, 3, 1, 1);
	} else {
		cairo_rectangle (ct2, 1, 3, 2, 1);
		cairo_rectangle (ct2, 2, 2, 2, 1);
		cairo_rectangle (ct2, 3, 1, 1, 1);
		cairo_rectangle (ct2, 0, 1, 1, 1);
		cairo_rectangle (ct2, 0, 0, 2, 1);
	}
	cairo_fill (ct2);

	cairo_destroy (ct2);
	return CAIRO_STATUS_SUCCESS;
}
