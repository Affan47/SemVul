callbacks_units_changed (gerbv_gui_unit_t unit) {
	static gboolean isChanging = FALSE;

	if (isChanging)
		return;

	isChanging = TRUE;
	screen.unit = unit;

	if (unit == GERBV_MILS){
		gtk_combo_box_set_active (GTK_COMBO_BOX (screen.win.statusUnitComboBox), GERBV_MILS);
		gtk_check_menu_item_set_active (screen.win.menu_view_unit_group[GERBV_MILS], TRUE);
	} else if (unit == GERBV_MMS){
		gtk_combo_box_set_active (GTK_COMBO_BOX (screen.win.statusUnitComboBox), GERBV_MMS);
		gtk_check_menu_item_set_active (screen.win.menu_view_unit_group[GERBV_MMS], TRUE);
	} else {
		gtk_combo_box_set_active (GTK_COMBO_BOX (screen.win.statusUnitComboBox), GERBV_INS);
		gtk_check_menu_item_set_active (screen.win.menu_view_unit_group[GERBV_INS], TRUE);
	}

	callbacks_update_ruler_scales ();
	callbacks_update_statusbar_coordinates (screen.last_x, screen.last_y);

	if (screen.tool == MEASURE)
		callbacks_update_statusbar_measured_distance (screen.win.lastMeasuredX, screen.win.lastMeasuredY);

	isChanging = FALSE;
}
