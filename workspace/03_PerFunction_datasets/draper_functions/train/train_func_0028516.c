ethi_add_drop_marker (ETableHeaderItem *ethi,
                      gint col,
                      gboolean recreate)
{
	GnomeCanvas *canvas;
	GtkAdjustment *adjustment;
	GdkWindow *window;
	gint rx, ry;
	gint x;

	if (!recreate && ethi->drag_mark == col)
		return;

	ethi->drag_mark = col;

	x = e_table_header_col_diff (ethi->eth, 0, col);
	if (col > 0)
		x += ethi->group_indent_width;

	if (!arrow_up) {
		arrow_up   = make_shaped_window_from_xpm (arrow_up_xpm);
		arrow_down = make_shaped_window_from_xpm (arrow_down_xpm);
	}

	canvas = GNOME_CANVAS_ITEM (ethi)->canvas;
	window = gtk_widget_get_window (GTK_WIDGET (canvas));
	gdk_window_get_origin (window, &rx, &ry);

	adjustment = gtk_scrollable_get_hadjustment (GTK_SCROLLABLE (canvas));
	rx -= gtk_adjustment_get_value (adjustment);

	adjustment = gtk_scrollable_get_vadjustment (GTK_SCROLLABLE (canvas));
	ry -= gtk_adjustment_get_value (adjustment);

	gtk_window_move (
		GTK_WINDOW (arrow_down),
		rx + x - ARROW_PTR,
		ry - ARROW_DOWN_HEIGHT);
	gtk_widget_show_all (arrow_down);

	gtk_window_move (
		GTK_WINDOW (arrow_up),
		rx + x - ARROW_PTR,
		ry + ethi->height);
	gtk_widget_show_all (arrow_up);
}
