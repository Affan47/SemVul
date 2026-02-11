sb_set_cursor ()
{
	static GdkCursor *cursor_normal = NULL, *cursor_busy = NULL,
		*cursor_inactive = NULL;

	if (!cursor_normal) cursor_normal = gdk_cursor_new (GDK_LEFT_PTR);
	if (!cursor_busy) cursor_busy = gdk_cursor_new (GDK_WATCH);
	if (!cursor_inactive) cursor_inactive = gdk_cursor_new (GDK_XTERM);
	if (player_to_play == MACHINE && !ui_stopped)
		gdk_window_set_cursor (board_area->window, cursor_busy);
	else if (player_to_play == MACHINE && ui_stopped)
		gdk_window_set_cursor (board_area->window, cursor_inactive);
	else
		gdk_window_set_cursor (board_area->window, cursor_normal);
}
