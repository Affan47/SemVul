cairo_surface_to_pixbuf (cairo_surface_t *surface)
{
	gint stride, width, height, x, y;
	guchar *data, *output, *output_pixel;


	g_assert (cairo_image_surface_get_format (surface) == CAIRO_FORMAT_RGB24);

	stride = cairo_image_surface_get_stride (surface);
	width = cairo_image_surface_get_width (surface);
	height = cairo_image_surface_get_height (surface);
	data = cairo_image_surface_get_data (surface);

	output = g_malloc (stride * height);
	output_pixel = output;

	for (y = 0; y < height; y++) {
		guint32 *row = (guint32*) (data + y * stride);

		for (x = 0; x < width; x++) {
			output_pixel[0] = (row[x] & 0x00ff0000) >> 16;
			output_pixel[1] = (row[x] & 0x0000ff00) >> 8;
			output_pixel[2] = (row[x] & 0x000000ff);

			output_pixel += 3;
		}
	}

	return gdk_pixbuf_new_from_data (output, GDK_COLORSPACE_RGB, FALSE, 8,
					 width, height, width * 3,
					 (GdkPixbufDestroyNotify) g_free, NULL);
}
