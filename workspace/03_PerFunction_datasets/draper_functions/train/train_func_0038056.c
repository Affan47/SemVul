nodoka_style_draw_vline (GtkStyle * style, GdkWindow * window,
						 GtkStateType state_type, GdkRectangle * area,
						 GtkWidget * widget, const gchar * detail, gint y1,
						 gint y2, gint x)
{
	SeparatorParameters separator = { FALSE };
	cairo_t *cr = nodoka_begin_paint (window, area);
	NodokaStyle *nodoka_style = NODOKA_STYLE (style);
	NodokaColors *colors = &nodoka_style->colors;

	if (!
		(widget && widget->parent && GTK_IS_HBOX (widget->parent) && widget->parent->parent
		 && GTK_IS_TOGGLE_BUTTON (widget->parent->parent) && widget->parent->parent->parent
		 && GTK_IS_COMBO_BOX (widget->parent->parent->parent)))
	{
		nodoka_draw_separator (cr, colors, NULL, &separator, x, y1, 2, y2 - y1);
	}
	else
		nodoka_draw_combo_separator (cr, colors, NULL, x, y1, 2, y2 - y1);
	cairo_destroy (cr);
}
