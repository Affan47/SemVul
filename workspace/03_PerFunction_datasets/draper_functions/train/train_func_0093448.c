release_device(pam_handle_t *pamh, DBusGProxy *dev)
{
	GError *error = NULL;
	if (!dbus_g_proxy_call (dev, "Release", &error, G_TYPE_INVALID, G_TYPE_INVALID)) {
		D(pamh, "ReleaseDevice failed: %s\n", error->message);
		g_error_free (error);
	}
}
