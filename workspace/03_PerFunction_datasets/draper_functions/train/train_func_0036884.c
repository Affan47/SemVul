gpk_prefs_upgrade_freq_combo_changed (GtkWidget *widget, GpkPrefsPrivate *priv)
{
	gchar *value;
	guint freq = 0;

	value = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (widget));
	if (strcmp (value, PK_FREQ_DAILY_TEXT) == 0)
		freq = GPK_PREFS_VALUE_DAILY;
	else if (strcmp (value, PK_FREQ_WEEKLY_TEXT) == 0)
		freq = GPK_PREFS_VALUE_WEEKLY;
	else if (strcmp (value, PK_FREQ_NEVER_TEXT) == 0)
		freq = GPK_PREFS_VALUE_NEVER;
	else
		g_assert (FALSE);

	g_debug ("Changing %s to %i", GSD_SETTINGS_FREQUENCY_GET_UPGRADES, freq);
	g_settings_set_int (priv->settings_gsd, GSD_SETTINGS_FREQUENCY_GET_UPGRADES, freq);
	g_free (value);
}
