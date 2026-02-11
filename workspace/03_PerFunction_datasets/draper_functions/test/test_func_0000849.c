mgicchikn_draw_focus (GtkStyle * style,
					  GdkWindow * window,
					  GtkStateType state_type,
					  GdkRectangle * area,
					  GtkWidget * widget,
					  const gchar * detail,
					  gint x,
					  gint y,
					  gint width,
					  gint height)
{
	GdkGC *gc = style->base_gc[GTK_STATE_SELECTED];
	GdkPoint points[5];
	gint line_width = 1,
	  dash_len;
	gchar *dash_list = "\1\1";
	gboolean free_dash_list = FALSE;

	sanitize_size (window, &width, &height);
	if (widget)
	{
		gtk_widget_style_get (widget,
							  "focus-line-width",
							  &line_width,
							  "focus-line-pattern", (gchar *) & dash_list, NULL);
		free_dash_list = TRUE;
	}

	if (area)
		gdk_gc_set_clip_rectangle (gc, area);
	gdk_gc_set_line_attributes (gc, line_width,
								dash_list[0] ?
								GDK_LINE_ON_OFF_DASH :
								GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_MITER);
	if (detail && !strcmp (detail, "add-mode"))
	{
		if (free_dash_list)
			g_free (dash_list);
		dash_list = "\4\4";
		free_dash_list = FALSE;
	}

	points[0].x = x + line_width / 2;
	points[0].y = y + line_width / 2;
	points[1].x = x + width - line_width + line_width / 2;
	points[1].y = y + line_width / 2;
	points[2].x = x + width - line_width + line_width / 2;
	points[2].y = y + height - line_width + line_width / 2;
	points[3].x = x + line_width / 2;
	points[3].y = y + height - line_width + line_width / 2;
	points[4] = points[0];
	if (!dash_list[0])
	{
		gdk_draw_lines (window, gc, points, 5);
	}
	else
	{


		dash_len = strlen (dash_list);
		if (dash_list[0])
			gdk_gc_set_dashes (gc, 0, dash_list, dash_len);
		gdk_draw_lines (window, gc, points, 3);


		points[2].x += 1;
		if (dash_list[0])
		{
			gint dash_pixels = 0;
			gint i;


			for (i = 0; i < dash_len; i++)
				dash_pixels += dash_list[i];
			if (dash_len % 2 == 1)
				dash_pixels *= 2;
			gdk_gc_set_dashes (gc,
							   dash_pixels - (width + height -
											  2 *
											  line_width) %
							   dash_pixels, dash_list, dash_len);
		}

		gdk_draw_lines (window, gc, points + 2, 3);
	}

	gdk_gc_set_line_attributes (gc, 0, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_MITER);
	if (area)
		gdk_gc_set_clip_rectangle (gc, NULL);
	if (free_dash_list)
		g_free (dash_list);
}
