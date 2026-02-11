nm_remote_connection_get_secrets (NMRemoteConnection *self,
                                  const char *setting_name,
                                  NMRemoteConnectionGetSecretsFunc callback,
                                  gpointer user_data)
{
	NMRemoteConnectionPrivate *priv;
	RemoteCall *call;

	g_return_if_fail (self != NULL);
	g_return_if_fail (NM_IS_REMOTE_CONNECTION (self));
	g_return_if_fail (callback != NULL);

	priv = NM_REMOTE_CONNECTION_GET_PRIVATE (self);

	call = g_malloc0 (sizeof (RemoteCall));
	call->self = self;
	call->callback = (GFunc) callback;
	call->user_data = user_data;

	call->call = dbus_g_proxy_begin_call (priv->proxy, "GetSecrets",
	                                      get_secrets_cb, call, NULL,
	                                      G_TYPE_STRING, setting_name,
	                                      G_TYPE_INVALID);
	g_assert (call->call);
	priv->calls = g_slist_append (priv->calls, call);
}
