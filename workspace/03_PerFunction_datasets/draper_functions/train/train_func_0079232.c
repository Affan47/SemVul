nodoka_style_draw_arrow (GtkStyle * style, GdkWindow * window,
						 GtkStateType state_type, GtkShadowType shadow,
						 GdkRectangle * area, GtkWidget * widget,
						 const gchar * detail, GtkArrowType arrow_type,
						 gboolean fill, gint x, gint y, gint width, gint height)
{
	NodokaStyle *nodoka_style = NODOKA_STYLE (style);
	NodokaColors *colors = &nodoka_style->colors;
	cairo_t *cr = nodoka_begin_paint (window, area);

	nodoka_sanitize_size (window, &width, &height);

	WidgetParameters params;
	ArrowParameters arrow;

	nodoka_set_widget_parameters (widget, style, state_type, &params);
	params.state_type = (NodokaStateType) state_type;
	arrow.type = NDK_ARROW_NORMAL;
	arrow.direction = (NodokaDirection) arrow_type;


	if (arrow_type == (GtkArrowType) 4)
	{
		cairo_destroy (cr);
		return;
	}

	if (widget && widget->parent && widget->parent->parent && widget->parent->parent->parent
	    && GTK_IS_COMBO_BOX (widget->parent->parent->parent) &&
	    !(GTK_IS_COMBO_BOX_ENTRY (widget->parent->parent->parent)))
		x += 1;


	if (DETAIL ("arrow"))
	{
		if (widget && GTK_IS_COMBO_BOX (widget))
		{
			arrow.type = NDK_ARROW_COMBO;
			y -= 2;
			height += 4;
			x += 1;
		}

	}
	else if (DETAIL ("hscrollbar") || DETAIL ("vscrollbar"))
	{
		arrow.type = NDK_ARROW_SCROLL;
		if (arrow.direction == NDK_DIRECTION_RIGHT)
			x--;
	}
	else if (DETAIL ("spinbutton"))
	{
		arrow.type = NDK_ARROW_SPINBUTTON;
	}

	nodoka_draw_arrow (cr, colors, &params, &arrow, x, y, width, height);

	cairo_destroy (cr);
}
