start_new_gameboard (GtkWidget *widget) {

	cairo_t *cr;

	if (tileset_sm) g_object_unref (tileset_sm);
	if (tileset_bg) g_object_unref (tileset_bg);

	tileset_sm = gdk_pixbuf_new_from_file_at_size (gc_theme,
						       ballsm*8+ballsm/2, ballsm, &error);
	tileset_bg = gdk_pixbuf_new_from_file_at_size (gc_theme,
						       ballmed*8+ballmed/2, ballmed, &error);
	if (error) {
		g_warning ("Failed to load '%s': %s", gc_theme, error->message);
		g_error_free (error);
		error = NULL;
	}

	if (gc_gtkstyle_colors) {


		bgcolor = widget->style->base[GTK_STATE_SELECTED];
		bgcolor.red = (bgcolor.red + (widget->style->white).red * 6.2 ) / 8;
		bgcolor.green = (bgcolor.green + (widget->style->white).green * 6.2 ) / 8;
		bgcolor.blue = (bgcolor.blue + (widget->style->white).blue * 6.2 ) / 8;


		fgcolor = widget->style->base[GTK_STATE_SELECTED];
		fgcolor.red = (fgcolor.red + (widget->style->black).red ) / 2;
		fgcolor.green = (fgcolor.green + (widget->style->black).green ) / 2;
		fgcolor.blue = (fgcolor.blue + (widget->style->black).blue ) / 2;

	} else {
		gdk_color_parse (gc_bgcolor, &bgcolor);
		gdk_color_parse (gc_fgcolor, &fgcolor);
	}
	if (GTK_IS_WIDGET (pref_dialog)) {
		gtk_color_button_set_color (GTK_COLOR_BUTTON (fg_colorbutton), &fgcolor);
		gtk_color_button_set_color (GTK_COLOR_BUTTON (bg_colorbutton), &bgcolor);
	}

	xpos = 0;
	ypos = grid_rows-1;
	if ((newgame != 0) && pixmap) {
		g_object_unref (pixmap);
		gm_debug ("unreferencing pixmap\n");
		pixmap = NULL;
	}
	if ((!pixmap) || newgame != 0) {
		pixmap = gdk_pixmap_new (widget->window,
					 widget->allocation.width,
					 widget->allocation.height,
					 -1);

		cr = gdk_cairo_create (pixmap);
		cairo_set_antialias (cr, CAIRO_ANTIALIAS_NONE);

		gdk_cairo_set_source_color (cr, &bgcolor);
		cairo_rectangle (cr, 0, 0, widget->allocation.width, widget->allocation.height);
		cairo_fill (cr);
		cairo_destroy (cr);

		draw_main_grid (widget);
	}

	gdk_window_invalidate_rect (widget->window, NULL, FALSE);

	return TRUE;
}
