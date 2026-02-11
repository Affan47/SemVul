print_footer (GtkSourcePrintCompositor *compositor,
	      cairo_t                  *cr)
{
	pango_cairo_update_layout (cr, compositor->priv->footer_layout);


	if (compositor->priv->footer_format_left != NULL)
		print_footer_string (compositor,
				     cr,
				     PANGO_ALIGN_LEFT,
				     compositor->priv->footer_format_left);


	if (compositor->priv->footer_format_right != NULL)
		print_footer_string (compositor,
				     cr,
				     PANGO_ALIGN_RIGHT,
				     compositor->priv->footer_format_right);


	if (compositor->priv->footer_format_center != NULL)
		print_footer_string (compositor,
				     cr,
				     PANGO_ALIGN_CENTER,
				     compositor->priv->footer_format_center);


	if (compositor->priv->footer_separator)
	{
		gdouble y = compositor->priv->paper_height -
			    compositor->priv->real_margin_bottom -
			    (1 - SEPARATOR_SPACING_FACTOR) * compositor->priv->footer_height;

		cairo_save (cr);

		cairo_move_to (cr, compositor->priv->real_margin_left, y);
		cairo_set_line_width (cr, SEPARATOR_LINE_WIDTH);
		cairo_line_to (cr, compositor->priv->paper_width - compositor->priv->real_margin_right, y);
		cairo_stroke (cr);

		cairo_restore (cr);
	}
}
