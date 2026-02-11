_gx_knob_draw_indicator(cairo_t *cr, GdkRectangle *image_rect, gdouble knobstate)
{

	double radius1 = min(image_rect->width, image_rect->height) / 2;
	double angle = scale_zero + knobstate * 2 * (M_PI - scale_zero);
	double add_angle = 90* (M_PI / 180.);
	cairo_set_source_rgb(cr,  0.2, 0.8, 0.2);
	cairo_set_line_width(cr, 4.0);
	cairo_arc (cr,image_rect->x+radius1,image_rect->y+radius1, radius1*0.8,add_angle+scale_zero,add_angle+angle);
	cairo_stroke(cr);
}
