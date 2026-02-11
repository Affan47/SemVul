draw_nbsp_at_iter (cairo_t      *cr,
		   GtkTextView  *view,
		   GtkTextIter  *iter,
		   GdkRectangle  rect,
		   gboolean      narrowed)
{
	gint x, y;
	gdouble w, h;

	gtk_text_view_buffer_to_window_coords (view,
	                                       GTK_TEXT_WINDOW_TEXT,
	                                       rect.x,
	                                       rect.y + rect.height / 2,
	                                       &x,
	                                       &y);


	w = rect.width ? rect.width : rect.height;
	h = rect.height;

	cairo_save (cr);
	cairo_move_to (cr, x + w * 1 / 6, y);
	cairo_rel_line_to (cr, w * 4 / 6, 0);
	cairo_rel_line_to (cr, -w * 2 / 6, +h * 1 / 4);
	cairo_rel_line_to (cr, -w * 2 / 6, -h * 1 / 4);

	if (narrowed)
	{
		cairo_fill (cr);
	}
	else
	{
		cairo_stroke (cr);
	}

	cairo_restore (cr);
}
