agent_save_delete_cb (DBusGProxy *proxy,
                      DBusGProxyCall *call,
                      void *user_data)
{
	Request *r = user_data;
	NMSecretAgentPrivate *priv = NM_SECRET_AGENT_GET_PRIVATE (r->agent);
	GError *error = NULL;

	g_return_if_fail (call == r->call);

	dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID);
	r->callback (r->agent, r->call, NULL, error, r->callback_data);
	g_clear_error (&error);
	g_hash_table_remove (priv->requests, call);
}
