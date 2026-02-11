configure_event_handler(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data)
{
	int t = -1;
	term_data *td;

	t = term_window_from_widget(widget);

	if (t != -1)
	{
		td = &data[t];

		if (td->initialized)
		{
			int x = 0, y = 0, w = 0, h = 0;
			GdkRectangle r;

			gdk_window_get_frame_extents(td->win->window, &r);
			x = r.x;
			y = r.y;

			gtk_window_get_size(GTK_WINDOW(td->win), &w, &h);

			td->location.x = x;
			td->location.y = y;

			if (w != 0) td->size.w = w;
			if (h != 0)  td->size.h = h;
		}
	}
	return(FALSE);
}
