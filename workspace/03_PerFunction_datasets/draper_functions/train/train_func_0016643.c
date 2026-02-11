panel_util_query_tooltip_cb (GtkWidget  *widget,
			     gint        x,
			     gint        y,
			     gboolean    keyboard_tip,
			     GtkTooltip *tooltip,
			     const char *text)
{
	GSettings *gsettings;
	gboolean   enable_tooltips;

	gsettings = g_settings_new (PANEL_GENERAL_SCHEMA);
	enable_tooltips = g_settings_get_boolean (gsettings,
						  PANEL_GENERAL_ENABLE_TOOLTIPS_KEY);
	g_object_unref (gsettings);

	if (!enable_tooltips)
		return FALSE;

	gtk_tooltip_set_text (tooltip, text);
	return TRUE;
}
