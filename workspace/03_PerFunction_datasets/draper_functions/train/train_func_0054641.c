highlight_updated_cb (GtkSourceBuffer *buffer,
		      GtkTextIter     *start,
		      GtkTextIter     *end,
		      GtkTextView     *text_view)
{
	GdkRectangle visible_rect;
	GdkRectangle updated_rect;
	GdkRectangle redraw_rect;
	gint y;
	gint height;


	gtk_text_view_get_visible_rect (text_view, &visible_rect);


	gtk_text_view_get_line_yrange (text_view, start, &y, &height);
	updated_rect.y = y;
	gtk_text_view_get_line_yrange (text_view, end, &y, &height);
	updated_rect.height = y + height - updated_rect.y;
	updated_rect.x = visible_rect.x;
	updated_rect.width = visible_rect.width;

	DEBUG ({
		g_print ("> highlight_updated start\n");
		g_print ("    lines udpated: %d - %d\n",
			 gtk_text_iter_get_line (start),
			 gtk_text_iter_get_line (end));
		g_print ("    visible area: %d - %d\n",
			 visible_rect.y, visible_rect.y + visible_rect.height);
		g_print ("    updated area: %d - %d\n",
			 updated_rect.y, updated_rect.y + updated_rect.height);
	});


	if (gdk_rectangle_intersect (&updated_rect, &visible_rect, &redraw_rect))
	{
		GdkRectangle widget_rect;

		gtk_text_view_buffer_to_window_coords (text_view,
						       GTK_TEXT_WINDOW_WIDGET,
						       redraw_rect.x,
						       redraw_rect.y,
						       &widget_rect.x,
						       &widget_rect.y);

		widget_rect.width = redraw_rect.width;
		widget_rect.height = redraw_rect.height;

		DEBUG ({
			g_print ("    invalidating: %d - %d\n",
				 widget_rect.y, widget_rect.y + widget_rect.height);
		});

		gtk_widget_queue_draw_area (GTK_WIDGET (text_view),
					    widget_rect.x,
					    widget_rect.y,
					    widget_rect.width,
					    widget_rect.height);
	}

	DEBUG ({
		g_print ("> highlight_updated end\n");
	});
}
