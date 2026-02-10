anjuta_window_set_geometry (AnjutaWindow *win, const gchar *geometry)
{
	gint width, height, posx, posy;
	gboolean geometry_set = FALSE;

	if (geometry && strlen (geometry) > 0)
	{
		DEBUG_PRINT ("Setting geometry: %s", geometry);

		if (sscanf (geometry, "%dx%d+%d+%d", &width, &height,
					&posx, &posy) == 4)
		{
			if (gtk_widget_get_realized (GTK_WIDGET (win)))
			{
				gtk_window_resize (GTK_WINDOW (win), width, height);
			}
			else
			{
				gtk_window_set_default_size (GTK_WINDOW (win), width, height);
				gtk_window_move (GTK_WINDOW (win), posx, posy);
			}
			geometry_set = TRUE;
		}
		else
		{
			g_warning ("Failed to parse geometry: %s", geometry);
		}
	}
	if (!geometry_set)
	{
		posx = 10;
		posy = 10;
		width = gdk_screen_width () - 10;
		height = gdk_screen_height () - 25;
		width = (width < 790)? width : 790;
		height = (height < 575)? width : 575;
		if (gtk_widget_get_realized (GTK_WIDGET (win)) == FALSE)
		{
			gtk_window_set_default_size (GTK_WINDOW (win), width, height);
			gtk_window_move (GTK_WINDOW (win), posx, posy);
		}
	}
}
