background_flush(gboolean force)
{

	if (force)
	{
		if (bg.gc)
		{
			g_object_unref(bg.gc);
			bg.gc = NULL;
		}

		if (bg.scaled)
		{
			g_object_unref(bg.scaled);
			bg.scaled = NULL;
		}
	}


	if (cfg.background_tiled)
	{
		if (bg.gc)
			return;

		if (bg.scaled)
		{
			g_object_unref(bg.scaled);
			bg.scaled = NULL;
		}

		GdkPixmap *tile;
		GtkWidget *playingarea_widget = glade_xml_get_widget (ui.xml, "playingarea");

		gdk_pixbuf_render_pixmap_and_mask_for_colormap (bg.original, gdk_colormap_get_system(), &tile, NULL, 127);
		bg.gc = gdk_gc_new(playingarea_widget->window);
		gdk_gc_set_tile(bg.gc, tile);
		gdk_gc_set_fill(bg.gc, GDK_TILED);
		g_object_unref(tile);
		return;
	}


	if (bg.gc)
	{
		g_object_unref(bg.gc);
		bg.gc = NULL;
	}


	GtkWidget *widget = glade_xml_get_widget(ui.xml, "playingarea");
	if (bg.scaled == NULL || widget->allocation.width != gdk_pixbuf_get_width(bg.scaled) || widget->allocation.height != gdk_pixbuf_get_height(bg.scaled))
	{
		if (bg.scaled)
			g_object_unref(bg.scaled);

		bg.scaled = gdk_pixbuf_scale_simple(bg.original, widget->allocation.width, widget->allocation.height, GDK_INTERP_BILINEAR);
	}
}
