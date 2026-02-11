callbacks_switch_to_normal_tool_cursor (gint toolNumber) {
	GdkCursor *cursor;

	switch (toolNumber) {
		case POINTER:
			gdk_window_set_cursor(GDK_WINDOW(screen.drawing_area->window),
						  GERBV_DEF_CURSOR);
			break;
		case PAN:
			cursor = gdk_cursor_new(GDK_FLEUR);
			gdk_window_set_cursor(GDK_WINDOW(screen.drawing_area->window),
					  cursor);
			gdk_cursor_destroy(cursor);
			break;
		case ZOOM:
			cursor = gdk_cursor_new(GDK_SIZING);
			gdk_window_set_cursor(GDK_WINDOW(screen.drawing_area->window),
					      cursor);
			gdk_cursor_destroy(cursor);
			break;
		case MEASURE:
			cursor = gdk_cursor_new(GDK_CROSSHAIR);
			gdk_window_set_cursor(GDK_WINDOW(screen.drawing_area->window),
					  cursor);
			gdk_cursor_destroy(cursor);
			break;
		default:
			break;
	}
}
