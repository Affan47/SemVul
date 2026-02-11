panel_menu_item_activate_switch_user (GtkWidget *menuitem,
				      gpointer   user_data)
{
	GdkScreen *screen;
	GAppInfo  *app_info;

	if (panel_lockdown_get_disable_switch_user_s ())
		return;

	screen = gtk_widget_get_screen (GTK_WIDGET (menuitem));
	app_info = g_app_info_create_from_commandline (GDM_FLEXISERVER_COMMAND " " GDM_FLEXISERVER_ARGS,
						       GDM_FLEXISERVER_COMMAND,
						       G_APP_INFO_CREATE_NONE,
						       NULL);

	if (app_info) {
		GdkAppLaunchContext *launch_context;
		GdkDisplay          *display;

		display = gdk_screen_get_display (screen);
		launch_context = gdk_display_get_app_launch_context (display);
		gdk_app_launch_context_set_screen (launch_context, screen);

		g_app_info_launch (app_info, NULL,
				   G_APP_LAUNCH_CONTEXT (launch_context),
				   NULL);

		g_object_unref (launch_context);
		g_object_unref (app_info);
	}
}
