gkrellm_render_data_pixmap(GkrellmPiximage *im, GdkPixmap **pixmap,
			GdkColor *color, gint h)
	{
	GtkWidget   *top_win = gkrellm_get_top_window();
	gint		w, w_pixmap = 0, h_pixmap = 0;

	w = gkrellm_chart_width();
	if (*pixmap)
		gdk_drawable_get_size(*pixmap, &w_pixmap, &h_pixmap);

	if (!*pixmap || w != w_pixmap || h != h_pixmap)
		{
		if (!gkrellm_scale_piximage_to_pixmap(im, pixmap, NULL, w, h))
			{
			*pixmap = gdk_pixmap_new(top_win->window, w, h, -1);
			if (color)
				gdk_gc_set_foreground(_GK.draw1_GC, color);
			else
				gdk_gc_set_foreground(_GK.draw1_GC, &_GK.in_color_grid);
			gdk_draw_rectangle(*pixmap, _GK.draw1_GC, TRUE, 0,0,w,h);
			}
		}
	}
