create_main_window (GtkWidget *notebook)
{
	char *s;
	int width;
	int height;

	genius_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	s = g_strdup_printf (_("Genius %s"), VERSION);
	gtk_window_set_title (GTK_WINDOW (genius_window), s);
	g_free (s);

	gtk_window_set_wmclass (GTK_WINDOW (genius_window), "gnome-genius", "gnome-genius");
	add_main_window_contents (genius_window, notebook);


	width = 800;
	height = 600;

	if (width > gdk_screen_width () * 0.75)
		width = gdk_screen_width () * 0.75;
	if (height > gdk_screen_height () * 0.75)
		height = gdk_screen_height () * 0.75;

	gtk_window_set_default_size (GTK_WINDOW (genius_window), width, height);

        g_signal_connect (G_OBJECT (genius_window), "delete_event",
			  G_CALLBACK (delete_event), NULL);
}
