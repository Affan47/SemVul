scale_or_ref (GdkPixbuf * src, int width, int height)
{
	if (width == gdk_pixbuf_get_width (src)
		&& height == gdk_pixbuf_get_height (src))
	{
		return g_object_ref (src);
	}
	else
	{
		return gdk_pixbuf_scale_simple (src, width, height,
										GDK_INTERP_BILINEAR);
	}
}
