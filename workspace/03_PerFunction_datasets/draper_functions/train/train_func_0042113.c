delete_cb (DBusGProxy *proxy, DBusGProxyCall *proxy_call, gpointer user_data)
{
	RemoteCall *call = user_data;
	NMRemoteConnectionDeleteFunc func = (NMRemoteConnectionDeleteFunc) call->callback;
	GError *error = NULL;

	dbus_g_proxy_end_call (proxy, proxy_call, &error,
	                       G_TYPE_INVALID);
	if (func != NULL)
		(*func)(call->self, error, call->user_data);
	g_clear_error (&error);
	remote_call_complete (call->self, call);
}
