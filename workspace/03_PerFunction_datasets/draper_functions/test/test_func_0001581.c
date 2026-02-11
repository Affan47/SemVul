gps_check_toggled (GtkCheckButton *btn, GeoclueTestGui *gui)
{
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (btn))) {
		gui->master_resources |= GEOCLUE_RESOURCE_GPS;
	} else {
		gui->master_resources &= ~GEOCLUE_RESOURCE_GPS;
	}
	update_master_requirements (gui);
}
