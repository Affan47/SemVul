sanity_check_window_dimensions (guint *width, guint *height)
{
	g_assert (width != NULL);
	g_assert (height != NULL);


	*width = MIN (*width, gdk_screen_width());
	*height = MIN (*height, gdk_screen_height());
}
