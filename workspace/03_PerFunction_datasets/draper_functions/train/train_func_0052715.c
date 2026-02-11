prop_set_auth_done_cb (NMAuthChain *chain,
                       GError *error,
                       DBusGMethodInvocation *context,
                       gpointer user_data)
{
	NMManager *self = NM_MANAGER (user_data);
	NMManagerPrivate *priv = NM_MANAGER_GET_PRIVATE (self);
	DBusGConnection *bus;
	DBusConnection *dbus_connection;
	NMAuthCallResult result;
	DBusMessage *reply = NULL, *request;
	GError *ret_error;
	const char *permission, *prop, *objpath;
	gboolean set_enabled = TRUE;
	gboolean is_device = FALSE;
	size_t objpath_len;
	size_t devpath_len;

	priv->auth_chains = g_slist_remove (priv->auth_chains, chain);

	request = nm_auth_chain_get_data (chain, "message");
	permission = nm_auth_chain_get_data (chain, "permission");
	prop = nm_auth_chain_get_data (chain, "prop");
	set_enabled = GPOINTER_TO_UINT (nm_auth_chain_get_data (chain, "enabled"));
	objpath = nm_auth_chain_get_data (chain, "objectpath");

	objpath_len = strlen (objpath);
	devpath_len = strlen (NM_DBUS_PATH "/Devices");
	if (   strncmp (objpath, NM_DBUS_PATH "/Devices", devpath_len) == 0
	    && objpath_len > devpath_len)
		is_device = TRUE;

	if (error) {
		reply = dbus_message_new_error (request, is_device ? DEV_PERM_DENIED_ERROR : NM_PERM_DENIED_ERROR,
		                                "Not authorized to perform this operation");
	} else {


		result = GPOINTER_TO_UINT (nm_auth_chain_get_data (chain, permission));
		if (result != NM_AUTH_CALL_RESULT_YES) {
			reply = dbus_message_new_error (request, is_device ? DEV_PERM_DENIED_ERROR : NM_PERM_DENIED_ERROR,
			                                "Not authorized to perform this operation");
		} else {
			if (is_device) {

				NMDevice *device = nm_manager_get_device_by_path (self, objpath);
				if (device) {
					g_object_set (device, prop, set_enabled, NULL);
					reply = dbus_message_new_method_return (request);
				}
				else {
					ret_error = g_error_new_literal (NM_MANAGER_ERROR,
					                                 NM_MANAGER_ERROR_UNKNOWN_DEVICE,
					                                 "Can't find device for this operation");
					dbus_g_method_return_error (context, ret_error);
					g_error_free (ret_error);
				}
			} else {
				g_object_set (self, prop, set_enabled, NULL);
				reply = dbus_message_new_method_return (request);
			}
		}
	}

	if (reply) {
		bus = nm_dbus_manager_get_connection (priv->dbus_mgr);
		g_assert (bus);
		dbus_connection = dbus_g_connection_get_connection (bus);
		g_assert (dbus_connection);

		dbus_connection_send (dbus_connection, reply, NULL);
		dbus_message_unref (reply);
	}
	nm_auth_chain_unref (chain);
}
