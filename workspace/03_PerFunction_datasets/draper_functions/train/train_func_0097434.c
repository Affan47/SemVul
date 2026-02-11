adj_value_changed_cb(GtkAdjustment* data, gpointer window)
{
	char *buffer;
	float freq = rint(gtk_adjustment_get_value(adj))/STEPS;
	const char *preset_title = get_preset(freq, &mom_ps);

	preset_combo_set_item(mom_ps);

	redraw_status_window();

	if (preset_title)
		buffer = g_strdup_printf(_("Gnomeradio - %s"), preset_title);
	else
		buffer = g_strdup_printf(_("Gnomeradio - %.2f MHz"), freq);
	gtk_window_set_title(GTK_WINDOW(window), buffer);
	tray_icon_set_title(buffer);
	g_free(buffer);

	buffer = g_strdup_printf(_("Frequency: %.2f MHz"), freq);
	gtk_widget_set_tooltip_text(freq_scale, buffer);
	g_free(buffer);

	radio_set_freq(gtk_adjustment_get_value(adj)/STEPS);
}
