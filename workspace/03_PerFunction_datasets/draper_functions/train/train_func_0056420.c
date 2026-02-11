giggle_graph_renderer_get_size (GtkCellRenderer    *cell,
                                GtkWidget          *widget,
                                const GdkRectangle *cell_area,
                                gint               *x_offset,
                                gint               *y_offset,
                                gint               *width,
                                gint               *height)
{
	GiggleGraphRendererPrivate *priv;
	GtkStyleContext            *context;
	const PangoFontDescription *font_desc;
	gint size;

	priv = GIGGLE_GRAPH_RENDERER (cell)->_priv;

	context = gtk_widget_get_style_context (widget);
	font_desc = gtk_style_context_get_font (context, gtk_widget_get_state_flags (widget));
	size = PANGO_PIXELS (pango_font_description_get_size (font_desc));

	if (height) {
		*height = PATH_SPACE (size);
	}

	if (width) {

		*width = PATH_SPACE (size) * (priv->n_paths + 1);
	}

	if (x_offset) {
		x_offset = 0;
	}

	if (y_offset) {
		y_offset = 0;
	}
}
