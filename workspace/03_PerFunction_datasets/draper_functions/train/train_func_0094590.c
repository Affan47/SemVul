e2_utils_update_gtk_settings (void)
{
	GtkSettings *defs = gtk_settings_get_default ();
	gint delay_up = e2_option_int_get ("submenu-up-delay");
	gint delay_down = e2_option_int_get ("submenu-down-delay");

	if (delay_up < 0) delay_up = 0;
	if (delay_down < 0) delay_down = 0;
	gtk_settings_set_long_property (defs, "gtk-menu-popup-delay",
		delay_up, "XProperty");
	gtk_settings_set_long_property (defs, "gtk-menu-popdown-delay",
		delay_down, "XProperty");
	gtk_settings_set_long_property (defs, "gtk-menubar-popup-delay",
		delay_up, "XProperty");

	g_object_get (G_OBJECT (defs), "gtk-double-click-time", &click_interval, NULL);
	if (click_interval < E2_CLICKINTERVAL)
	{
		click_interval = E2_CLICKINTERVAL;
		g_object_set (G_OBJECT (defs), "gtk-double-click-time", E2_CLICKINTERVAL, NULL);
	}

}
