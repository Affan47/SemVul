notified_signal_handler (DBusGProxy *proxy, const char *msg, gpointer user_data)
{
	if (!user_data || !MIDGARD_IS_DBUS(user_data))
		return;

	MidgardDbus *mbus = MIDGARD_DBUS(user_data);

	if (mbus->priv->message)
		g_free(mbus->priv->message);

	mbus->priv->message = g_strdup(msg);

	g_signal_emit(mbus, MIDGARD_DBUS_GET_CLASS(mbus)->signal_notified, 0, mbus->priv->message);
}
