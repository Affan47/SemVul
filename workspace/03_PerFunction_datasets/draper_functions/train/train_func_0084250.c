draw_stat (GitgStatView    *view,
           cairo_t         *ctx,
           gdouble         *color,
           cairo_pattern_t *gradient,
           gint             x,
           gint             y,
           gint             width,
           gint             height)
{
	gdouble darker[3];
	gdouble xoff;
	cairo_matrix_t mat;

	x += 0.5;
	y += 0.5;
	width -= 1;
	height -= 1;

	gitg_utils_rounded_rectangle (ctx,
	                              x,
	                              y,
	                              width,
	                              height,
	                              view->priv->radius);

	cairo_set_source (ctx, gradient);
	cairo_fill_preserve (ctx);

	multiply_color (color, 0.4, darker);

	cairo_set_line_width (ctx, 1);

	cairo_set_source_rgb (ctx, darker[0], darker[1], darker[2]);
	cairo_stroke (ctx);

	if (view->priv->show_lines)
	{
		xoff = x + view->priv->lines_spacing;

		cairo_matrix_init_rotate (&mat, M_PI);
		cairo_pattern_set_matrix (gradient, &mat);

		cairo_set_source (ctx, gradient);

		while (xoff < x + width - view->priv->lines_spacing / 2)
		{
			cairo_move_to (ctx, xoff, y + 2);
			cairo_line_to (ctx, xoff, y + height - 2);
			cairo_stroke (ctx);

			xoff += view->priv->lines_spacing;
		}

		cairo_matrix_init_identity (&mat);
		cairo_pattern_set_matrix (gradient, &mat);
	}
}
