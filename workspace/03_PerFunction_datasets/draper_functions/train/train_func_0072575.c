set_charset_cb(GtkAction *action, GtkRadioAction *current, gpointer data)
{
	MainWindow *mainwin = (MainWindow *)data;
	gint value = gtk_radio_action_get_current_value (GTK_RADIO_ACTION (current));
	const gchar *str;

	if (gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (current))) {
		str = conv_get_charset_str((CharSet)value);

		g_free(mainwin->messageview->forced_charset);
		mainwin->messageview->forced_charset = str ? g_strdup(str) : NULL;
		procmime_force_charset(str);

		summary_redisplay_msg(mainwin->summaryview);

		debug_print("forced charset: %s\n", str ? str : "Auto-Detect");
	}
}
