gw_capture_box_disk_name_ok ( GtkWidget *w, gpointer data) {
	gchar *disk_name;
	GtkWindow *window = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( data != NULL ) {
		window = gw_gui_manager_main_interface_get_main_window ( );

		if ( window != NULL ) {
			disk_name = gw_capture_box_get_text ( data);
			gw_notebook_managment_set_device_name ( window, disk_name);
			g_free ( disk_name);


			gtk_widget_destroy ( data);
			gw_notebook_managment_scan_click ( NULL, window);

			result = 0;
		}
	}

	return result;
}
