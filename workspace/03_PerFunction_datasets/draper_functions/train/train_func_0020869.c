murrine_style_draw_tab (DRAW_ARGS)
{
	MurrineStyle *murrine_style = MURRINE_STYLE (style);
	MurrineColors *colors = &murrine_style->colors;

	cairo_t *cr;

	CHECK_ARGS
	SANITIZE_SIZE

	cr = murrine_begin_paint (window, area);

	WidgetParameters params;
	ArrowParameters  arrow;

	arrow.type      = MRN_ARROW_COMBO;
	arrow.direction = MRN_DIRECTION_DOWN;
	arrow.style     = murrine_style->arrowstyle;

	murrine_set_widget_parameters (widget, style, state_type, &params);

	STYLE_FUNCTION(draw_arrow) (cr, colors, &params, &arrow, x, y, width, height);

	cairo_destroy (cr);
}
