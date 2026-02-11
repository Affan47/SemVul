prefs_show_label_get (AlarmApplet *applet)
{
	GConfClient *client = gconf_client_get_default ();
	GConfValue *value;
	gboolean state;


	value = gconf_client_get(client, ALARM_GCONF_DIR "/show_label", NULL);
	if (value == NULL) {
		g_warning ("Get %s failed", ALARM_GCONF_DIR "/show_label");
		return gtk_toggle_action_get_active (applet->action_toggle_show_label);
	}

	state = gconf_value_get_bool (value);
	gconf_value_free (value);

	return state;
}
