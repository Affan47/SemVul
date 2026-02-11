_tp_channel_dispatch_operation_new_with_factory (TpSimpleClientFactory *factory,
    TpDBusDaemon *bus_daemon,
    const gchar *object_path,
    GHashTable *immutable_properties,
    GError **error)
{
  TpChannelDispatchOperation *self;
  gchar *unique_name;

  g_return_val_if_fail (bus_daemon != NULL, NULL);
  g_return_val_if_fail (object_path != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (!tp_dbus_check_valid_object_path (object_path, error))
    return NULL;

  if (!_tp_dbus_daemon_get_name_owner (bus_daemon, -1,
      TP_CHANNEL_DISPATCHER_BUS_NAME, &unique_name, error))
    return NULL;

  self = TP_CHANNEL_DISPATCH_OPERATION (g_object_new (
        TP_TYPE_CHANNEL_DISPATCH_OPERATION,
        "dbus-daemon", bus_daemon,
        "bus-name", unique_name,
        "object-path", object_path,
        "cdo-properties", immutable_properties,
        "factory", factory,
        NULL));

  g_free (unique_name);

  return self;
}
