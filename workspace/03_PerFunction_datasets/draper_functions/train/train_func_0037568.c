callbacks_change_tool (GtkButton *button, gpointer   user_data) {
	gint toolNumber = GPOINTER_TO_INT (user_data);


	if (screen.win.updatingTools)
		return;
	screen.win.updatingTools = TRUE;
	gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (screen.win.toolButtonPointer), FALSE);
	gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (screen.win.toolButtonPan), FALSE);
	gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (screen.win.toolButtonZoom), FALSE);
	gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (screen.win.toolButtonMeasure), FALSE);
	switch (toolNumber) {
		case POINTER:
			gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (screen.win.toolButtonPointer), TRUE);
			screen.tool = POINTER;
			screen.state = NORMAL;
			snprintf(screen.statusbar.diststr, MAX_DISTLEN,
				 "Click to select objects in the current layer. Middle click and drag to pan.");
			break;
		case PAN:
			gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (screen.win.toolButtonPan), TRUE);
			screen.tool = PAN;
			screen.state = NORMAL;
			snprintf(screen.statusbar.diststr, MAX_DISTLEN,
				 "Click and drag to pan. Right click and drag to zoom.");
			break;
		case ZOOM:
			gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (screen.win.toolButtonZoom), TRUE);
			screen.tool = ZOOM;
			screen.state = NORMAL;
			snprintf(screen.statusbar.diststr, MAX_DISTLEN,
				 "Click and drag to zoom in. Shift+click to zoom out.");
			break;
		case MEASURE:
			gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (screen.win.toolButtonMeasure), TRUE);
			screen.tool = MEASURE;
			screen.state = NORMAL;
			snprintf(screen.statusbar.diststr, MAX_DISTLEN, "Click and drag to measure a distance.");
			break;
		default:
			break;
	}
	callbacks_switch_to_normal_tool_cursor (toolNumber);
	callbacks_update_statusbar();
	screen.win.updatingTools = FALSE;
	callbacks_force_expose_event_for_screen();
}
