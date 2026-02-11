gw_notebook_managment_refresh_info ( GtkWidget *chk, GtkWindow *w) {
	GtkCombo *cmb = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL ) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_DISPLAY_INFO, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
	}

	if ( w != NULL ) {
		if ( (cmb = gw_notebook_managment_get_combo_box_device ( w)) != NULL) {
			result = gw_notebook_managment_select_device ( GTK_WIDGET ( GTK_OBJECT ( GTK_ENTRY ( GTK_COMBO ( cmb)->entry))), w);
		}
	}

	return result;
}
