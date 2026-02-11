subscribe_cal_cb(GtkAction *action, gpointer data)
{
	gchar *uri = NULL;
	gchar *tmp = NULL;

	tmp = input_dialog(_("Subscribe to WebCal"), _("Enter the WebCal URL:"), NULL);
	if (tmp == NULL)
		return;

	if (!strncmp(tmp, "http", 4)) {
		uri = tmp;
	} else if (!strncmp(tmp, "file://", 7)) {
		uri = tmp;
	} else if (!strncmp(tmp, "webcal", 6)) {
		uri = g_strconcat("http", tmp+6, NULL);
		g_free(tmp);
	} else {
		alertpanel_error(_("Could not parse the URL."));
		g_free(tmp);
		return;
	}
	debug_print("uri %s\n", uri);

	update_subscription(uri, TRUE);
	folder_write_list();
	g_free(uri);
}
