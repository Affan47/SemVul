equinox_style_draw_shadow_gap (DRAW_ARGS,
			      GtkPositionType gap_side,
			      gint gap_x, gint gap_width) {
	EquinoxStyle *equinox_style = EQUINOX_STYLE (style);
	EquinoxColors *colors = &equinox_style->colors;
	cairo_t *cr;

	CHECK_ARGS
	SANITIZE_SIZE
	cr = equinox_begin_paint (window, area);

	if (DETAIL ("frame")) {
		WidgetParameters params;
		FrameParameters frame;

		frame.shadow = shadow_type;
		frame.gap_side = gap_side;
		frame.gap_x = gap_x;
		frame.gap_width = gap_width;
		frame.border = (EquinoxRGB *) & colors->shade[FRAME_SHADE];
		frame.use_fill = FALSE;
		frame.fill_bg = TRUE;

		equinox_set_widget_parameters (widget, style, state_type, &params);
		params.curvature = MIN(params.curvature, MIN(params.xthickness, params.ythickness) + 1.5);

		equinox_draw_frame (cr, colors, &params, &frame, x-1, y-1, width+2, height+2);
	} else {
		equinox_parent_class->draw_shadow_gap (style, window, state_type,
					  shadow_type, area, widget, detail,
					  x, y, width, height, gap_side,
					  gap_x, gap_width);
	}
	cairo_destroy (cr);
}
