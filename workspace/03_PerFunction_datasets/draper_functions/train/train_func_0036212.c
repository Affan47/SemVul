on_session_bus_acquired (GDBusConnection    *connection,
                         const char         *unique_name,
                         GoaIdentityService *self)
{
  goa_debug ("GoaIdentityService: Connected to session bus");

  if (self->priv->connection == NULL)
  {
    self->priv->connection = g_object_ref (connection);

    g_dbus_object_manager_server_set_connection (self->priv->object_manager_server,
                                                 self->priv->connection);

    goa_client_new (NULL,
                    (GAsyncReadyCallback)
                    on_got_client,
                    self);
  }
}
