tp_connection_manager_dispose (GObject *object)
{
  TpConnectionManager *self = TP_CONNECTION_MANAGER (object);
  TpProxy *as_proxy = (TpProxy *) self;

  if (self->priv->disposed)
    goto finally;

  self->priv->disposed = TRUE;

  tp_dbus_daemon_cancel_name_owner_watch (as_proxy->dbus_daemon,
      as_proxy->bus_name, tp_connection_manager_name_owner_changed_cb,
      object);

  if (self->priv->protocol_structs != NULL)
    {
      g_ptr_array_unref (self->priv->protocol_structs);
      self->priv->protocol_structs = NULL;
    }

  if (self->priv->protocol_objects != NULL)
    {
      g_hash_table_unref (self->priv->protocol_objects);
      self->priv->protocol_objects = NULL;
    }

  if (self->priv->found_protocols != NULL)
    {
      g_hash_table_unref (self->priv->found_protocols);
      self->priv->found_protocols = NULL;
    }

finally:
  G_OBJECT_CLASS (tp_connection_manager_parent_class)->dispose (object);
}
