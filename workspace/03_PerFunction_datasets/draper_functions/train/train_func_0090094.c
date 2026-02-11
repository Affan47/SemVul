gpk_update_viewer_check_mobile_broadband (void)
{
	gboolean ret = TRUE;
	PkNetworkEnum state;
	const gchar *message;


	g_object_get (control,
		      "network-state", &state,
		      NULL);


	gtk_widget_hide (info_mobile);


	if (state != PK_NETWORK_ENUM_MOBILE)
		goto out;


	if (size_total < GPK_UPDATE_VIEWER_MOBILE_SMALL_SIZE)
		goto out;


	ret = g_settings_get_boolean (settings, GPK_SETTINGS_NOTIFY_MOBILE_CONNECTION);
	if (!ret)
		goto out;


	message = ngettext ("Connectivity is being provided by wireless broadband, and it may be expensive to update this package.",
			    "Connectivity is being provided by wireless broadband, and it may be expensive to update these packages.",
			    number_total);
	gtk_label_set_label (GTK_LABEL(info_mobile_label), message);

	gtk_info_bar_set_message_type (GTK_INFO_BAR(info_mobile), GTK_MESSAGE_WARNING);
	gtk_widget_show (info_mobile);
out:
	return;
}
