sensor_reset_optionmenu(Sensor *sensor)
	{
	Sensor	*sr;

	if (!optionmenu)
		return;
	sr = get_referenced_sensor();
	if (sr == sensor)
		gtk_option_menu_set_history(GTK_OPTION_MENU(optionmenu),
					SENSOR_PANEL_LOCATION);
	}
