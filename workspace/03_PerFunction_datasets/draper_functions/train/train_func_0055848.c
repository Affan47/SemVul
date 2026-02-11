e2_window_set_title (GtkWidget *wid, const gchar *title)
{
	if (title != NULL)
	{
		gchar *tt = e2_utils_strcat (PROGNAME ": ", title);
		gtk_window_set_title (GTK_WINDOW (wid), tt);
		g_free (tt);
	}
	else
		gtk_window_set_title (GTK_WINDOW (wid), PROGNAME);
}
