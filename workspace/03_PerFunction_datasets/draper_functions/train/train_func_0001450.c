e_dbus_object_skeleton_get_property (GObject      *gobject,
  guint         prop_id,
  GValue       *value,
  GParamSpec   *pspec)
{
  EDBusObjectSkeleton *object = E_DBUS_OBJECT_SKELETON (gobject);
  GDBusInterface *interface;

  switch (prop_id)
    {
    case 1:
      interface = g_dbus_object_get_interface (G_DBUS_OBJECT (object), "org.gnome.evolution.dataserver.Source");
      g_value_take_object (value, interface);
      break;

    case 2:
      interface = g_dbus_object_get_interface (G_DBUS_OBJECT (object), "org.gnome.evolution.dataserver.Source.Removable");
      g_value_take_object (value, interface);
      break;

    case 3:
      interface = g_dbus_object_get_interface (G_DBUS_OBJECT (object), "org.gnome.evolution.dataserver.Source.Writable");
      g_value_take_object (value, interface);
      break;

    case 4:
      interface = g_dbus_object_get_interface (G_DBUS_OBJECT (object), "org.gnome.evolution.dataserver.Source.RemoteCreatable");
      g_value_take_object (value, interface);
      break;

    case 5:
      interface = g_dbus_object_get_interface (G_DBUS_OBJECT (object), "org.gnome.evolution.dataserver.Source.RemoteDeletable");
      g_value_take_object (value, interface);
      break;

    case 6:
      interface = g_dbus_object_get_interface (G_DBUS_OBJECT (object), "org.gnome.evolution.dataserver.Source.OAuth2Support");
      g_value_take_object (value, interface);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
      break;
  }
}
