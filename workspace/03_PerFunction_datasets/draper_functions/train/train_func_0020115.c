gossip_cell_renderer_expander_get_size (GtkCellRenderer *cell,
					GtkWidget       *widget,
					const GdkRectangle *cell_area,
					gint            *x_offset,
					gint            *y_offset,
					gint            *width,
					gint            *height)
{
	GossipCellRendererExpander     *expander;
	GossipCellRendererExpanderPriv *priv;
	gint                            xpad, ypad;
	gfloat                          xalign, yalign;

	expander = (GossipCellRendererExpander*) cell;
	priv = GET_PRIV (expander);
	gtk_cell_renderer_get_padding (cell, &xpad, &ypad);

	if (cell_area) {

		gtk_cell_renderer_get_alignment (cell, &xalign, &yalign);

		if (x_offset) {
			*x_offset = xalign * (cell_area->width - (priv->expander_size + (2 * xpad)));
			*x_offset = MAX (*x_offset, 0);
		}

		if (y_offset) {
			*y_offset = yalign * (cell_area->height - (priv->expander_size + (2 * ypad)));
			*y_offset = MAX (*y_offset, 0);
		}
	} else {
		if (x_offset)
			*x_offset = 0;

		if (y_offset)
			*y_offset = 0;
	}

	if (width)
		*width = xpad * 2 + priv->expander_size;

	if (height)
		*height = ypad * 2 + priv->expander_size;
}
