_tp_account_new_with_factory (TpSimpleClientFactory *factory,
    TpDBusDaemon *bus_daemon,
    const gchar *object_path,
    GError **error)
{
  TpAccount *self;

  g_return_val_if_fail (TP_IS_DBUS_DAEMON (bus_daemon), NULL);
  g_return_val_if_fail (object_path != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  if (!tp_account_parse_object_path (object_path, NULL, NULL, NULL, error))
    return NULL;
  G_GNUC_END_IGNORE_DEPRECATIONS

  self = TP_ACCOUNT (g_object_new (TP_TYPE_ACCOUNT,
          "dbus-daemon", bus_daemon,
          "dbus-connection", ((TpProxy *) bus_daemon)->dbus_connection,
          "bus-name", TP_ACCOUNT_MANAGER_BUS_NAME,
          "object-path", object_path,
          "factory", factory,
          NULL));

  return self;
}
