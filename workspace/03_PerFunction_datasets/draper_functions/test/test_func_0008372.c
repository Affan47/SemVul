draw_confetti_hatch (cairo_surface_t *hatch, GpHatch *hbr)
{
	double hatch_size = gdip_hatch_get_width (hbr);
	double confetti_size = (hbr->hatchStyle == HatchStyleLargeConfetti) ? 1.5 : 1.0;

	cairo_t *ct2 = create_hatch_context (hatch, CAIRO_LINE_CAP_SQUARE, FALSE);
	if (ct2 == NULL)
		return CAIRO_STATUS_NO_MEMORY;

	draw_background (ct2, hbr->backColor, hatch_size, hatch_size);

	set_color (ct2, hbr->foreColor);

	cairo_rectangle (ct2, 0, 0, confetti_size, confetti_size);
	cairo_rectangle (ct2, hatch_size / 8.0, hatch_size / 4.0, confetti_size, confetti_size);
	cairo_rectangle (ct2, 3 * hatch_size / 8.0, hatch_size / 2.0, confetti_size, confetti_size);
	cairo_rectangle (ct2, hatch_size / 4.0, 3 * hatch_size / 4.0, confetti_size, confetti_size);

	cairo_rectangle (ct2, hatch_size / 2.0, hatch_size / 8.0, confetti_size, confetti_size);
	cairo_rectangle (ct2, 3 * hatch_size / 4.0, 3 * hatch_size / 8.0, confetti_size, confetti_size);
	cairo_rectangle (ct2, 7 * hatch_size / 8.0, 5 * hatch_size / 8.0, confetti_size, confetti_size);
	cairo_rectangle (ct2, 5 * hatch_size / 8.0, 7 * hatch_size / 8.0, confetti_size, confetti_size);
	cairo_fill (ct2);

	cairo_destroy (ct2);
	return CAIRO_STATUS_SUCCESS;
}
