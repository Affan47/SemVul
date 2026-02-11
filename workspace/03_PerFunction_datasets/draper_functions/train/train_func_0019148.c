mgicchikn_util_set_pixbuf_transparency (const GdkPixbuf * pixbuf,
										gfloat alpha_percent)
{
	GdkPixbuf *target;
	guchar *line,
	 *pixel;
	guint x,
	  y,
	  rowstride,
	  height,
	  width;

	g_return_val_if_fail (pixbuf != NULL, NULL);
	g_return_val_if_fail (GDK_IS_PIXBUF (pixbuf), NULL);

	if (alpha_percent == 1.0)
		return GDK_PIXBUF (pixbuf);

	target = gdk_pixbuf_add_alpha (pixbuf, FALSE, 0, 0, 0);

	width = gdk_pixbuf_get_width (target);
	height = gdk_pixbuf_get_height (target);
	rowstride = gdk_pixbuf_get_rowstride (target);

	line = gdk_pixbuf_get_pixels (target);

	for (y = 0; y < height; y++)
	{
		pixel = line;
		for (x = 0; x < width; x++)
		{
			pixel[ALPHA_OFFSET] = CLAMP_UCHAR (pixel[ALPHA_OFFSET] * alpha_percent);
			pixel += PIXEL_SIZE_WITH_ALPHA;
		}
		line += rowstride;
	}

	return target;
}
