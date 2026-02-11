murrine_draw_progressbar_trough (cairo_t *cr,
                                 const MurrineColors    *colors,
                                 const WidgetParameters *widget,
                                 const ProgressBarParameters *progressbar,
                                 int x, int y, int width, int height)
{
	MurrineRGB border, fill;
	int roundness = MIN (widget->roundness, MIN ((height-2.0)/2.0, (width-2.0)/2.0));
	boolean horizontal = progressbar->orientation < 2;

	murrine_shade (&colors->bg[GTK_STATE_ACTIVE], 1.0, &fill);
	murrine_shade (&colors->bg[GTK_STATE_ACTIVE], murrine_get_contrast(0.82, widget->contrast), &border);


	murrine_draw_trough (cr, &fill, x+1, y+1, width-2, height-2, roundness-1, widget->corners, widget->mrn_gradient, 1.0, horizontal);


	murrine_draw_trough_border (cr, &border, x+0.5, y+0.5, width-1, height-1, roundness, widget->corners, widget->mrn_gradient, 1.0, horizontal);

	if (widget->mrn_gradient.gradients &&
	    widget->mrn_gradient.trough_shades[0] == 1.0 &&
	    widget->mrn_gradient.trough_shades[1] == 1.0)
	{
		cairo_pattern_t  *pat;
		MurrineRGB        shadow;

		murrine_shade (&border, 0.94, &shadow);


		murrine_rounded_rectangle_closed (cr, x+1, y+1, width-2, height-2, roundness, widget->corners);
		cairo_clip (cr);


		cairo_rectangle (cr, x+1, y+1, width-2, 4);
		pat = cairo_pattern_create_linear (x, y, x, y+4);
		murrine_pattern_add_color_stop_rgba (pat, 0.0, &shadow, 0.24);
		murrine_pattern_add_color_stop_rgba (pat, 1.0, &shadow, 0.);
		cairo_set_source (cr, pat);
		cairo_fill (cr);
		cairo_pattern_destroy (pat);


		cairo_rectangle (cr, x+1, y+1, 4, height-2);
		pat = cairo_pattern_create_linear (x, y, x+4, y);
		murrine_pattern_add_color_stop_rgba (pat, 0.0, &shadow, 0.24);
		murrine_pattern_add_color_stop_rgba (pat, 1.0, &shadow, 0.);
		cairo_set_source (cr, pat);
		cairo_fill (cr);
		cairo_pattern_destroy (pat);
	}
}
