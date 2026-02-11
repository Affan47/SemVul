ekiga_dbus_component_new (Ekiga::ServiceCore& service_core)
{
  DBusGConnection *bus;
  GError *error = NULL;
  EkigaDBusComponent *obj;

  bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
  if (!bus) {
    PTRACE (1, "Couldn't connect to session bus : " << error->message);
    g_error_free (error);
    return NULL;
  }

  obj = EKIGA_DBUS_COMPONENT (g_object_new (EKIGA_TYPE_DBUS_COMPONENT, NULL));
  obj->priv->service_core = &service_core;
  dbus_g_connection_register_g_object (bus, EKIGA_DBUS_PATH, G_OBJECT (obj));

  return obj;
}
