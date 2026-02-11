gcm_inspect_show_x11_atoms (void)
{
	gboolean ret;
	guint8 *data = NULL;
	gsize length = 0;
	GError *error = NULL;
	guint major = -1;
	guint minor = -1;
	GdkWindow *gdk_window;


	gdk_window = gdk_screen_get_root_window (gdk_screen_get_default ());


	ret = gcm_inspect_get_screen_profile_data (gdk_window, &data, &length, &error);
	if (!ret) {
		g_warning ("failed to get XServer profile data: %s", error->message);
		g_error_free (error);

		error = NULL;
	} else {

		gcm_inspect_print_data_info (_("Root window profile:"), data, length);
	}


	ret = gcm_inspect_get_screen_protocol_version (gdk_window, &major, &minor, &error);
	if (!ret) {
		g_warning ("failed to get XServer protocol version: %s", error->message);
		g_error_free (error);

		error = NULL;
	} else {

		g_print ("%s %i.%i\n", _("Root window protocol version:"), major, minor);
	}
	g_free (data);
	return ret;
}
