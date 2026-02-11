sw_core_constructed (GObject *object)
{
  SwCore *core = SW_CORE (object);
  SwCorePrivate *priv = core->priv;
  GError *error = NULL;
  const char *modules;

  priv->banned_uids = sw_ban_load (NULL);

  priv->connection = dbus_g_bus_get (DBUS_BUS_STARTER, &error);
  if (error) {
    g_warning ("Failed to open connection to DBus: %s\n", error->message);
    g_error_free (error);
  }

  dbus_g_connection_register_g_object (priv->connection,
                                       "/com/meego/libsocialweb",
                                       object);

  sw_client_monitor_init (priv->connection);

  modules = g_getenv ("SW_MODULES");
  if (modules) {
    load_modules_from_string (core, modules);
  } else {
    setup_modules_monitor (core);
    load_modules_from_dir (core);
  }

  sw_online_add_notify (online_changed, object);
}
