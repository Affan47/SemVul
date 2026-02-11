delete_auth_cb (NMSettingsConnection *self,
                DBusGMethodInvocation *context,
                gulong sender_uid,
                GError *error,
                gpointer data)
{
	if (error) {
		dbus_g_method_return_error (context, error);
		return;
	}

	nm_settings_connection_delete (self, con_delete_cb, context);
}
