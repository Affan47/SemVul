miner_resumed (GDBusConnection *connection,
               const gchar     *sender_name,
               const gchar     *object_path,
               const gchar     *interface_name,
               const gchar     *signal_name,
               GVariant        *parameters,
               gpointer         user_data)
{
	MinerData *data = user_data;
	if (data->manager) {
		g_signal_emit (data->manager, signals[MINER_RESUMED], 0, data->dbus_name);
	}
}
