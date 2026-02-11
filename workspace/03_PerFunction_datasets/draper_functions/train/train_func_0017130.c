gp_image_invert_colors ( GpImage *image)
{
	gint width, height, rowstride, n_channels;
	gint x, y;
	guchar *pixels, *p;

	g_return_if_fail ( GP_IS_IMAGE (image) );

	n_channels = gdk_pixbuf_get_n_channels (image->priv->pixbuf);
	g_return_if_fail (gdk_pixbuf_get_colorspace (image->priv->pixbuf) == GDK_COLORSPACE_RGB);
	g_return_if_fail (gdk_pixbuf_get_bits_per_sample (image->priv->pixbuf) == 8);
	g_return_if_fail (gdk_pixbuf_get_has_alpha (image->priv->pixbuf));
	g_return_if_fail (n_channels == 4);
	width = gdk_pixbuf_get_width (image->priv->pixbuf);
	height = gdk_pixbuf_get_height (image->priv->pixbuf);
	rowstride = gdk_pixbuf_get_rowstride (image->priv->pixbuf);

	pixels = gdk_pixbuf_get_pixels (image->priv->pixbuf);

	for(y = 0; y < height; y++){
		for(x = 0; x < width; x++){
			p = pixels + y * rowstride + x * n_channels;
			p[0] = ~p[0];
			p[1] = ~p[1];
			p[2] = ~p[2];
		}
	}
}
