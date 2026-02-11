auth_start (NMSettingsConnection *self,
            DBusGMethodInvocation *context,
            const char *check_permission,
            AuthCallback callback,
            gpointer callback_data)
{
	NMSettingsConnectionPrivate *priv = NM_SETTINGS_CONNECTION_GET_PRIVATE (self);
	NMAuthChain *chain;
	gulong sender_uid = G_MAXULONG;
	GError *error = NULL;

	if (!check_user_in_acl (NM_CONNECTION (self),
	                        context,
	                        priv->dbus_mgr,
	                        priv->session_monitor,
	                        &sender_uid,
	                        &error)) {
		callback (self, context, G_MAXULONG, error, callback_data);
		g_clear_error (&error);
		return;
	}

	if (check_permission) {
		chain = nm_auth_chain_new (context, NULL, pk_auth_cb, self);
		g_assert (chain);
		nm_auth_chain_set_data (chain, "perm", (gpointer) check_permission, NULL);
		nm_auth_chain_set_data (chain, "callback", callback, NULL);
		nm_auth_chain_set_data (chain, "callback-data", callback_data, NULL);
		nm_auth_chain_set_data_ulong (chain, "sender-uid", sender_uid);

		nm_auth_chain_add_call (chain, check_permission, TRUE);
		priv->pending_auths = g_slist_append (priv->pending_auths, chain);
	} else {

		callback (self, context, sender_uid, NULL, callback_data);
	}
}
