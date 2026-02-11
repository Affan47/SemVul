nodoka_draw_focus (cairo_t * cr, const NodokaColors * colors, const WidgetParameters * widget,
				const FocusParameters * focus, int x, int y, int width, int height)
{
	NodokaRGB focus_ring;

	focus_ring.r = colors->spot[1].r * 0.3 + colors->spot[2].r * 0.7;
	focus_ring.g = colors->spot[1].g * 0.3 + colors->spot[2].g * 0.7;
	focus_ring.b = colors->spot[1].b * 0.3 + colors->spot[2].b * 0.7;

	cairo_translate (cr, x, y);
	cairo_set_line_width (cr, 1.0);


	cairo_set_source_rgb (cr, focus_ring.r, focus_ring.g, focus_ring.b);
	nodoka_rounded_rectangle_fast (cr, 0.5, 0.5,
						  width - 1,
						  height - 1, widget->roundness,
						  widget->corners);
	cairo_stroke (cr);


	if (focus->fill)
	{
		cairo_set_source_rgba (cr, focus_ring.r, focus_ring.g, focus_ring.b, 0.05);
		nodoka_rounded_rectangle (cr, 1, 1,
						  width - 2,
						  height - 2, widget->roundness - 1,
						  widget->corners);
		cairo_fill (cr);
	}


	if (focus->inner && !(focus->fill))
		cairo_set_source_rgba (cr, focus_ring.r, focus_ring.g, focus_ring.b, 0.5);
	else
		cairo_set_source_rgba (cr, focus_ring.r, focus_ring.g, focus_ring.b, 0.35);


	if (focus->inner)
	{
		nodoka_rounded_rectangle_fast (cr, 1.5, 1.5,
						  width - 3,
						  height - 3, widget->roundness - 1,
						  widget->corners);
	}
	else
	{
		nodoka_rounded_rectangle_fast (cr, -0.5, -0.5,
						  width + 1,
						  height + 1, widget->roundness + 1,
						  widget->corners);
	}

	cairo_stroke (cr);

	cairo_translate (cr, -x, -y);
}
