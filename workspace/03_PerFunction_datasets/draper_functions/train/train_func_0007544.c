gt_pixbuf_render_pixmap_and_mask(GdkPixbuf *pixbuf, GdkPixmap **pixmap_return, GdkBitmap **mask_return, int alpha_threshold)
{
	GdkColormap *colormap = gdk_rgb_get_colormap();
  GdkScreen *screen;

  screen = gdk_colormap_get_screen (colormap);

  if (pixmap_return)
	{
		GdkGC *gc;
		*pixmap_return = gdk_pixmap_new (gdk_screen_get_root_window (screen),
							gdk_pixbuf_get_width (pixbuf), gdk_pixbuf_get_height (pixbuf),
							gdk_colormap_get_visual (colormap)->depth);

		gdk_drawable_set_colormap (GDK_DRAWABLE (*pixmap_return), colormap);

		gc = gdk_gc_new(*pixmap_return);

		gt_pixmap_fill(*pixmap_return, 0, gc);

		gdk_draw_pixbuf (*pixmap_return, gc, pixbuf,
					0, 0, 0, 0,
					gdk_pixbuf_get_width (pixbuf), gdk_pixbuf_get_height (pixbuf),
					GDK_RGB_DITHER_NORMAL,
					0, 0);

		g_object_unref(gc);
	}

  if (mask_return)
	{
		if (gdk_pixbuf_get_has_alpha (pixbuf))
		{
			*mask_return = gdk_pixmap_new (gdk_screen_get_root_window (screen),
							gdk_pixbuf_get_width (pixbuf), gdk_pixbuf_get_height (pixbuf), 1);

			gdk_pixbuf_render_threshold_alpha (pixbuf, *mask_return,
									0, 0, 0, 0,
									gdk_pixbuf_get_width (pixbuf), gdk_pixbuf_get_height (pixbuf),
									alpha_threshold);
		}
		else
			*mask_return = NULL;
	}
}
