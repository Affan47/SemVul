mouseover_win(GtkWidget * widget,
			 GdkEventButton * event, gpointer data)
{
	Win *win = (Win *) data;
	g_signal_handler_disconnect(G_OBJECT(win->win), win->handlerid);
	win->handlerid =
		g_signal_connect(G_OBJECT(win->win),
				 "leave-notify-event",
				 G_CALLBACK(mouseout_win), data);
	if (win->timeout_id) {
		g_source_remove(win->timeout_id);
		win->timeout_id = 0;
	}
	return TRUE;
}
