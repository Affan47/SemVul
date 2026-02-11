utils_get_hex_from_color(GdkColor *color)
{
	gchar *buffer = g_malloc0(9);

	g_return_val_if_fail(color != NULL, NULL);

	g_snprintf(buffer, 8, "#%02X%02X%02X",
	      (guint) (utils_scale_round(color->red / 256, 255)),
	      (guint) (utils_scale_round(color->green / 256, 255)),
	      (guint) (utils_scale_round(color->blue / 256, 255)));

	return buffer;
}
