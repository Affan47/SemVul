gpk_update_viewer_check_restart (void)
{
	GtkWindow *window;
	GtkWidget *dialog;
	gboolean ret = FALSE;
	const gchar *title;
	const gchar *message;
	const gchar *button;
	GtkResponseType response;
	gboolean show_button = TRUE;
	GError *error = NULL;


	title = gpk_restart_enum_to_localised_text (restart_update);
	if (restart_update == PK_RESTART_ENUM_SYSTEM) {

		message = _("Some of the updates that were installed require the computer to be restarted before the changes will be applied.");

		button = _("Restart Computer");

	} else if (restart_update == PK_RESTART_ENUM_SECURITY_SYSTEM) {

		message = _("Some of the updates that were installed require the computer to be restarted to remain secure.");

		button = _("Restart Computer");

	} else if (restart_update == PK_RESTART_ENUM_SESSION) {

		message = _("Some of the updates that were installed require you to log out and back in before the changes will be applied.");

		button = _("Log Out");

	} else if (restart_update == PK_RESTART_ENUM_SECURITY_SESSION) {

		message = _("Some of the updates that were installed require you to log out and back in to remain secure.");

		button = _("Log Out");

	} else {
		g_warning ("unknown restart enum");
		goto out;
	}


	window = GTK_WINDOW(gtk_builder_get_object (builder, "dialog_updates"));
	dialog = gtk_message_dialog_new (window, GTK_DIALOG_MODAL,
					 GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
					 "%s", title);


	if (restart_update == PK_RESTART_ENUM_SYSTEM ||
	    restart_update == PK_RESTART_ENUM_SECURITY_SYSTEM) {
#ifdef HAVE_SYSTEMD
                systemd_proxy_can_restart (proxy, &show_button, NULL);
#else
		egg_console_kit_can_restart (console, &show_button, NULL);
#endif
	}


	if (show_button)
		gtk_dialog_add_button (GTK_DIALOG (dialog), button, GTK_RESPONSE_OK);
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG(dialog), "%s", message);
	gtk_window_set_icon_name (GTK_WINDOW(dialog), GPK_ICON_SOFTWARE_UPDATE);
	response = gtk_dialog_run (GTK_DIALOG(dialog));
	gtk_widget_destroy (dialog);


	if (response != GTK_RESPONSE_OK)
		goto out;


	ret = TRUE;


	if (restart_update == PK_RESTART_ENUM_SYSTEM)
#ifdef HAVE_SYSTEMD
                ret = systemd_proxy_restart (proxy, &error);
#else

		ret = egg_console_kit_restart (console, &error);
#endif
		if (!ret) {

			gpk_update_viewer_error_dialog (_("Could not restart"), NULL, error->message);
			g_error_free (error);
		}
	else if (restart_update == PK_RESTART_ENUM_SESSION) {
		GpkSession *session;
		session = gpk_session_new ();

		gpk_session_logout (session);
		g_object_unref (session);
	}
out:
	return ret;
}
