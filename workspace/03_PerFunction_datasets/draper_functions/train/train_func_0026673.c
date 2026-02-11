start_procman (MultiloadApplet *ma)
{
	GError *error = NULL;
	GDesktopAppInfo *appinfo;
	gchar *monitor;
	GdkAppLaunchContext *launch_context;
	GAppInfo *app_info;
	GdkScreen *screen;

	g_return_if_fail (ma != NULL);

	monitor = panel_applet_gconf_get_string (ma->applet, "system_monitor", NULL);
	if (monitor == NULL)
	        monitor = g_strdup ("gnome-system-monitor.desktop");

	screen = gtk_widget_get_screen (GTK_WIDGET (ma->applet));
	appinfo = g_desktop_app_info_new (monitor);
	if (appinfo) {
		GdkAppLaunchContext *context;

		context = gdk_app_launch_context_new ();
		gdk_app_launch_context_set_screen (context, screen);
		gdk_app_launch_context_set_timestamp (context,
						      gtk_get_current_event_time ());

		g_app_info_launch_uris (G_APP_INFO (appinfo), NULL,
					(GAppLaunchContext *) context,
					&error);

		g_object_unref (context);
		g_object_unref (appinfo);

		if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
			g_error_free (error);
			error = NULL;
		}
	}
	else {
		app_info = g_app_info_create_from_commandline ("gnome-system-monitor",
							      _("Start system-monitor"),
							      G_APP_INFO_CREATE_NONE,
							      &error);

		if (!error) {
			launch_context = gdk_app_launch_context_new ();
			gdk_app_launch_context_set_screen (launch_context, screen);
			g_app_info_launch (app_info, NULL, G_APP_LAUNCH_CONTEXT (launch_context), &error);

			g_object_unref (launch_context);
		}
	}
	g_free (monitor);

	if (error) {
		GtkWidget *dialog;

		dialog = gtk_message_dialog_new (NULL,
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_OK,
						 _("There was an error executing '%s': %s"),
						 "gnome-system-monitor",
						 error->message);

		g_signal_connect (dialog, "response",
				  G_CALLBACK (gtk_widget_destroy),
				  NULL);

		gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
		gtk_window_set_screen (GTK_WINDOW (dialog),
				       gtk_widget_get_screen (GTK_WIDGET (ma->applet)));

		gtk_widget_show (dialog);

		g_error_free (error);
	}
}
