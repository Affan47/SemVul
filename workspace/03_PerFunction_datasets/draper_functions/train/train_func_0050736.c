on_button_pause_clicked(GtkButton *button, gpointer user_data) {
	GtkButton *tmpbutt = (GtkButton*) gtk_builder_get_object(builder, "button_pause");
	GTimeVal tmptime;
	if (paused) {
		if (rsync_pid) kill(rsync_pid, SIGCONT);
		gtk_button_set_label(tmpbutt, "gtk-media-pause");
		set_rsync_title(groups[session_last], "running");
		g_get_current_time(&tmptime);
		startime.tv_sec += tmptime.tv_sec - pausedtime.tv_sec;
		startime.tv_usec += tmptime.tv_usec - pausedtime.tv_usec;
	} else {
		if (rsync_pid) kill(rsync_pid, SIGSTOP);
		gtk_button_set_label(tmpbutt, "gtk-media-play");
		set_rsync_title(groups[session_last], "paused");
		g_get_current_time(&pausedtime);
		g_idle_add(scroll_idle, gtk_builder_get_object(builder, "textview_output"));
	}
	paused = !paused;
}
