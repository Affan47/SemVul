close_poi_lookup_window_cb (GtkWidget *window)
{

	if (!route.active)
	{
		coords.target_lat = wp_saved_target_lat;
		coords.target_lon = wp_saved_target_lon;
	}
	if (gui_status.posmode)
	{
		coords.posmode_lat = wp_saved_posmode_lat;
		coords.posmode_lon = wp_saved_posmode_lon;
	}

	gtk_widget_hide_all (poi_lookup_window);
	gtk_widget_set_sensitive (find_poi_bt, TRUE);
	gtk_widget_set_sensitive (posbt, TRUE);
}
