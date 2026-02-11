ev_object_proxy_get_property (GObject      *gobject,
  guint         prop_id,
  GValue       *value,
  GParamSpec   *pspec)
{
  EvObjectProxy *object = EV_OBJECT_PROXY (gobject);
  GDBusInterface *interface;

  switch (prop_id)
    {
    case 1:
      interface = g_dbus_object_get_interface (G_DBUS_OBJECT (object), "org.gnome.evince.Daemon");
      g_value_take_object (value, interface);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
      break;
  }
}
