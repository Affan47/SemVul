show_status_window()
{
	int win_x, win_y;
	unsigned int win_w, win_h;
	int flags;


#ifndef __MINGW32__
	if (geometry[0] != 0) {
		flags = XParseGeometry(geometry, &win_x, &win_y, &win_w,
			&win_h);
		gtk_window_set_position(GTK_WINDOW(statuswindow),
			GTK_WIN_POS_NONE);
		gtk_window_move(GTK_WINDOW(statuswindow), win_x, win_y);
		gtk_window_set_default_size(GTK_WINDOW(statuswindow), win_w,
			win_h);
	} else
#endif
	{
		if (iGetLocalPref("x_contact_window") > 0
			&& iGetLocalPref("y_contact_window") > 0)
			gtk_window_move(GTK_WINDOW(statuswindow),
				iGetLocalPref("x_contact_window"),
				iGetLocalPref("y_contact_window"));
	}

	gtk_widget_show(statuswindow);
#ifndef __MINGW32__
	if (geometry[0] == 0)
#endif
	{

		if (iGetLocalPref("x_contact_window") > 0
			&& iGetLocalPref("y_contact_window") > 0) {


			while (gtk_events_pending())
				gtk_main_iteration();

			gtk_window_move(GTK_WINDOW(statuswindow),
				iGetLocalPref("x_contact_window"),
				iGetLocalPref("y_contact_window"));
		}
	}
}
