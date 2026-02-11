check_ntp_support (GstTool  *tool)
{
	GstTimeToolPrivate *priv = GST_TIME_TOOL_GET_PRIVATE (tool);
	GtkWidget *message, *widget;
	gint response;

	if (GST_TIME_TOOL (tool)->ntp_service)
		return TRUE;
	else {

		oobs_object_update (OOBS_OBJECT (GST_TIME_TOOL (tool)->services_config));
		get_ntp_service (GST_TIME_TOOL (tool));

		if (GST_TIME_TOOL (tool)->ntp_service)
			return TRUE;
	}

	widget = gst_dialog_get_widget (tool->main_dialog, "configuration_options");
	g_signal_handler_block (widget, priv->configuration_changed_id);
	gtk_combo_box_set_active (GTK_COMBO_BOX (widget), CONFIGURATION_MANUAL);
	g_signal_handler_unblock (widget, priv->configuration_changed_id);

	message = gtk_message_dialog_new (GTK_WINDOW (tool->main_dialog),
					  GTK_DIALOG_MODAL,
					  GTK_MESSAGE_INFO,
					  GTK_BUTTONS_CLOSE,
					  _("NTP support is not installed"));
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (message),
						  _("Please install and activate NTP support in the system to enable "
						    "synchronization of your local time server with "
						    "internet time servers."));

	gtk_dialog_add_button (GTK_DIALOG (message), _("Install NTP support"), GTK_RESPONSE_OK);
	response = gtk_dialog_run (GTK_DIALOG (message));
	gtk_widget_destroy (message);

	if (response == GTK_RESPONSE_OK) {
		const gchar *packages[] = { "ntp", NULL };

		if (gst_packages_install (GTK_WINDOW (tool->main_dialog), packages)) {
			gtk_combo_box_set_active (GTK_COMBO_BOX (widget), CONFIGURATION_AUTOMATIC);
			gst_tool_update_config (tool);
			gst_tool_update_gui (tool);

			if (GST_TIME_TOOL (tool)->ntp_service)
				return TRUE;
		}
	}

	return FALSE;
}
