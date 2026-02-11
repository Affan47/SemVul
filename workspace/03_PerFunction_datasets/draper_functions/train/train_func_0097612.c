quit_event_handler(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
	if (save_game_gtk())
	{
		save_prefs();
		quit(NULL);
		exit(0);
		return(FALSE);
	}
	else
		return(TRUE);
}
