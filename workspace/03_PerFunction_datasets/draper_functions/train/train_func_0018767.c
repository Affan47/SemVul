aurora_style_draw_shadow_gap (DRAW_ARGS,
			      GtkPositionType gap_side,
			      gint gap_x, gint gap_width)
{
	AuroraStyle *aurora_style = AURORA_STYLE (style);
	AuroraColors *colors = &aurora_style->colors;
	cairo_t *cr;

	CHECK_ARGS
	SANITIZE_SIZE
	cr = aurora_begin_paint (window, area);

	if (DETAIL ("frame") && shadow_type != GTK_SHADOW_NONE) {
		WidgetParameters params;
		FrameParameters frame;

		frame.shadow = shadow_type;
		frame.gap_side = gap_side;
		frame.gap_x = gap_x;
		frame.gap_width = gap_width;
		frame.border = (AuroraRGB *) & colors->shade[FRAME_SHADE];
		frame.use_fill = FALSE;
		frame.fill_bg = TRUE;

		aurora_set_widget_parameters (widget, style, state_type, &params);
		params.curvature = MIN(params.curvature, MIN(params.xthickness, params.ythickness) + 1.5);

		aurora_draw_frame (cr, colors, &params, &frame, x-1, y-1, width+2, height+2);
	}


  cairo_destroy (cr);
}
