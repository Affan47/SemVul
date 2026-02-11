nodoka_style_draw_extension (DRAW_ARGS, GtkPositionType gap_side)
{
	NodokaStyle *nodoka_style = NODOKA_STYLE (style);
	NodokaColors *colors = &nodoka_style->colors;
	cairo_t *cr = nodoka_begin_paint (window, area);

	if (DETAIL ("tab"))
	{
		WidgetParameters params;
		TabParameters tab;

		nodoka_set_widget_parameters (widget, style, state_type, &params);
		params.corners = NDK_CORNER_NONE;

		tab.gap_side = (NodokaGapSide) gap_side;

		if (nodoka_style->roundness > 0)
		{
			if (gap_side == GTK_POS_BOTTOM)
				params.corners = NDK_CORNER_TOPLEFT | NDK_CORNER_TOPRIGHT;
			else if (gap_side == GTK_POS_TOP)
				params.corners = NDK_CORNER_BOTTOMLEFT | NDK_CORNER_BOTTOMRIGHT;
			else if (gap_side == GTK_POS_LEFT)
				params.corners = NDK_CORNER_TOPRIGHT | NDK_CORNER_BOTTOMRIGHT;
			else if (gap_side == GTK_POS_RIGHT)
				params.corners = NDK_CORNER_TOPLEFT | NDK_CORNER_BOTTOMLEFT;
		}
		else
			params.corners = NDK_CORNER_NONE;

		nodoka_draw_tab (cr, colors, &params, &tab, x, y, width, height);
	}
	else
	{
		nodoka_parent_class->draw_extension (style, window, state_type,
											 shadow_type, area, widget, detail,
											 x, y, width, height, gap_side);
	}

	cairo_destroy (cr);
}
