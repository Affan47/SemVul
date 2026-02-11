gog_renderer_get_pixbuf (GogRenderer *rend)
{
	g_return_val_if_fail (GOG_IS_RENDERER (rend), NULL);

	if (rend->cairo_surface == NULL)
		return NULL;

	if (rend->pixbuf == NULL) {
		int width = cairo_image_surface_get_width (rend->cairo_surface);
		int height = cairo_image_surface_get_height (rend->cairo_surface);
		int rowstride = cairo_image_surface_get_stride (rend->cairo_surface);
		unsigned char *data = cairo_image_surface_get_data (rend->cairo_surface);

		rend->pixbuf = gdk_pixbuf_new_from_data (data, GDK_COLORSPACE_RGB, TRUE, 8,
							 width, height, rowstride, NULL, NULL);
		go_cairo_convert_data_to_pixbuf (data, NULL, width, height, rowstride);
	}

	return rend->pixbuf;
}
