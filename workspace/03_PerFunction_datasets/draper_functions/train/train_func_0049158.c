color_from_hsb (gdouble hue, gdouble saturation, gdouble brightness)
{
	Color *color;

	color = g_new0 (Color, 1);
	gtk_hsv_to_rgb (hue, saturation, brightness,
			&color->red, &color->green, &color->blue);

	return color;
}
