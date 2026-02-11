gg_svg_draw_polygon (cairo_t * cairo, struct gg_svg_shape *shape,
		     struct gg_svg_style *style)
{

    int iv;
    struct gg_svg_polygon *poly = shape->data;
    if (poly->points <= 0 || poly->x == NULL || poly->y == NULL)
	return;
    if (style->visibility == 0)
	return;
    if (style->fill == 0 && style->stroke == 0)
	return;


    for (iv = 0; iv < poly->points; iv++)
      {
	  if (iv == 0)
	      cairo_move_to (cairo, *(poly->x + iv), *(poly->y + iv));
	  else
	      cairo_line_to (cairo, *(poly->x + iv), *(poly->y + iv));
      }
    cairo_close_path (cairo);
    if (style->fill)
      {

	  gg_svg_set_brush (cairo, style);
	  if (style->stroke)
	      cairo_fill_preserve (cairo);
	  else
	      cairo_fill (cairo);
      }
    if (style->stroke)
      {

	  gg_svg_set_pen (cairo, style);
	  cairo_stroke (cairo);
      }
}
