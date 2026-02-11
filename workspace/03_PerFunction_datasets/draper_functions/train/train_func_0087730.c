load_settings (void)
{
	GSettings *gsettings;
	gint count;
	double freq;

	gsettings = g_settings_new ("org.gnome.gnomeradio");
	g_settings_delay (gsettings);


	settings.device = g_settings_get_string (gsettings, "device");
	if ((settings.device == NULL) || (!strcmp (settings.device, "")))
		settings.device = g_strdup ("auto");
	settings.driver = g_settings_get_string (gsettings, "driver");
	if ((settings.driver == NULL) || (!strcmp (settings.driver, "")))
		settings.driver = g_strdup ("any");
	settings.mixer = g_settings_get_string (gsettings, "mixer");
	if ((settings.mixer == NULL) || (!strcmp (settings.mixer, "")))
		settings.mixer = g_strdup ("hw:0/Line");
	settings.audio_loopback = g_settings_get_boolean (gsettings, "audio-loopback");
	settings.mute_on_exit = g_settings_get_boolean (gsettings, "mute-on-exit");

	freq = g_settings_get_double (gsettings, "last-freq");
	if (freq < FREQ_MIN) freq = FREQ_MIN;
	if (freq > FREQ_MAX) freq = FREQ_MAX;
	gtk_adjustment_set_value(adj, freq * STEPS);


	rec_settings.destination = g_settings_get_string (gsettings, "destination");
	if ((rec_settings.destination == NULL) || (!strcmp (rec_settings.destination, "")))
		rec_settings.destination = g_strdup (g_get_home_dir());
	rec_settings.profile = g_settings_get_string (gsettings, "profile");
	if ((rec_settings.profile == NULL) || (!strcmp (rec_settings.profile, "")))
		rec_settings.profile = g_strdup ("audio/x-vorbis");


	presets_load ();

	count = g_settings_get_int (gsettings, "presets");
	mom_ps = g_settings_get_int (gsettings, "last");
	if (mom_ps >= count)
		mom_ps = -1;

	g_clear_object (&gsettings);
}
