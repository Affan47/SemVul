gossip_cell_renderer_expander_render (GtkCellRenderer      *cell,
				      cairo_t              *cr,
				      GtkWidget            *widget,
				      const GdkRectangle   *background_area,
				      const GdkRectangle   *cell_area,
				      GtkCellRendererState  flags)
{
	GossipCellRendererExpander     *expander;
	GossipCellRendererExpanderPriv *priv;
	GtkStyleContext                *style_context;
	gint                            x_offset, y_offset;
	gint                            xpad, ypad;
	GtkStateFlags                   state;

	expander = (GossipCellRendererExpander*) cell;
	priv = GET_PRIV (expander);

	gossip_cell_renderer_expander_get_size (cell, widget, cell_area,
						&x_offset, &y_offset,
						NULL, NULL);
	gtk_cell_renderer_get_padding (cell, &xpad, &ypad);

	style_context = gtk_widget_get_style_context (widget);

	gtk_style_context_save (style_context);
	gtk_style_context_add_class (style_context, GTK_STYLE_CLASS_EXPANDER);

	state = gtk_cell_renderer_get_state (cell, widget, flags);

	if (priv->expander_style == GTK_EXPANDER_COLLAPSED) {
		state |= GTK_STATE_FLAG_NORMAL;
	} else {
		state |= GTK_STATE_FLAG_ACTIVE;
	}

	gtk_style_context_set_state (style_context, state);

	gtk_render_expander (style_context,
			     cr,
			     cell_area->x + x_offset + xpad,
			     cell_area->y + y_offset + ypad,
			     priv->expander_size,
			     priv->expander_size);

	gtk_style_context_restore (style_context);
}
