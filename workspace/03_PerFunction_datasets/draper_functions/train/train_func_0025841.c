vfs_connection_setup (GDBusConnection *connection,
		      gboolean async)
{
  VfsConnectionData *connection_data;

  connection_data = g_new0 (VfsConnectionData, 1);

  g_object_set_data_full (G_OBJECT (connection), "connection_data", connection_data, connection_data_free);

  g_signal_connect (connection, "closed", G_CALLBACK (vfs_connection_closed), NULL);
}
