gw_gui_manager_main_interface_create ( ) {
	GtkWidget *main_window = NULL;
	GtkWidget *vbox = NULL;
	GtkWidget *menu_bar = NULL;
	GtkWidget *tool_bar = NULL;
	GtkWidget *notebook = NULL;
	GtkWidget *status_bar = NULL;
	GtkAccelGroup *accel_group = NULL;
	gint x = -1;
	gint y = -1;
	gint height = -1;
	gint width = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	accel_group = gtk_accel_group_new ( );


	main_window = gtk_window_new ( GTK_WINDOW_TOPLEVEL);
	window = GTK_WINDOW ( main_window);
	gtk_window_set_policy ( window, TRUE, TRUE, FALSE);


	if ( (height = gw_am_get_settings_tol ( GW_VALUE_APP_WIN_HEIGHT)) < 0 ) {
		height = GW_VALUE_APP_WIN_HEIGHT_DEFAULT;
	}
	height = MIN ( height, gdk_screen_height ( ));

	if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_WIN_WIDTH)) < 0 ) {
		width = GW_VALUE_APP_WIN_WIDTH_DEFAULT;
	}
	width = MIN ( width, gdk_screen_width ( ));

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "window size is %dx%d", width, height);
#endif


	gtk_window_set_default_size ( GTK_WINDOW ( main_window), width, height);


	if ( ((x = gw_am_get_settings_tol ( GW_VALUE_APP_WIN_X)) >= 0) && ((y = gw_am_get_settings_tol ( GW_VALUE_APP_WIN_Y)) >= 0) ) {
		 gtk_widget_set_uposition ( main_window, x, y);
	} else {
		gtk_window_set_position ( GTK_WINDOW ( main_window), GTK_WIN_POS_CENTER);
	}


	gtk_window_set_title ( GTK_WINDOW ( main_window), PROJECT_NAME);
  	gtk_signal_connect ( GTK_OBJECT ( main_window), "delete_event", GTK_SIGNAL_FUNC ( gw_menu_file_exit_click), NULL);
  	gtk_signal_connect ( GTK_OBJECT ( main_window), "destroy", GTK_SIGNAL_FUNC ( gw_menu_file_exit_click), NULL);
	gtk_widget_realize ( main_window);


	vbox = gtk_vbox_new ( FALSE, 0);
	gtk_widget_ref ( vbox);
	gtk_object_set_data_full ( GTK_OBJECT ( main_window), "VbMainWindow", vbox, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( main_window), vbox);


	menu_bar = gw_menu_create ( window, accel_group, vbox);
	gtk_box_pack_start ( GTK_BOX ( vbox), menu_bar, FALSE, FALSE, 0);


	tool_bar = gw_tool_bar_create_and_add ( window, vbox);


	notebook = gw_notebook_create ( window, vbox);
	gtk_box_pack_start ( GTK_BOX ( vbox), notebook, TRUE, TRUE, 0);


	status_bar = gw_status_bar_create_and_add ( window, vbox);

	gtk_window_add_accel_group ( window, accel_group);

	return window;
}
