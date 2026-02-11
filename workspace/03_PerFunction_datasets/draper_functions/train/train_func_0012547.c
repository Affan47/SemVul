gkrellm_clone_pixmap(GdkPixmap **dest, GdkPixmap **src)
	{
	gint	w_dest = 0, h_dest = 0, w_src = 0, h_src = 0;

	if (!dest)
		return FALSE;
	if (!src || !*src)
		{
		gkrellm_free_pixmap(dest);
		return FALSE;
		}
	gdk_drawable_get_size(*src, &w_src, &h_src);
	if (*dest)
		{
		gdk_drawable_get_size(*dest, &w_dest, &h_dest);
		if (w_dest != w_src || h_dest != h_src)
			gkrellm_free_pixmap(dest);
		}
	if (!*dest)
		*dest = gdk_pixmap_new(gkrellm_get_top_window()->window,
					w_src, h_src, -1);
	gdk_draw_drawable(*dest, _GK.draw1_GC, *src, 0, 0, 0, 0, w_src, h_src);
	return TRUE;
	}
