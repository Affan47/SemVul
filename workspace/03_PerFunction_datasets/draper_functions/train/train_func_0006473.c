tp_dbus_daemon_register_object (TpDBusDaemon *self,
    const gchar *object_path,
    gpointer object)
{
  TpProxy *as_proxy = (TpProxy *) self;

  g_return_if_fail (TP_IS_DBUS_DAEMON (self));
  g_return_if_fail (tp_dbus_check_valid_object_path (object_path, NULL));
  g_return_if_fail (G_IS_OBJECT (object));

  dbus_g_connection_register_g_object (as_proxy->dbus_connection,
      object_path, object);
}
