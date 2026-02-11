goa_realm_object_skeleton_set_property (GObject      *gobject,
  guint         prop_id,
  const GValue *value,
  GParamSpec   *pspec)
{
  GoaRealmObjectSkeleton *object = GOA_REALM_OBJECT_SKELETON (gobject);
  GDBusInterfaceSkeleton *interface;

  switch (prop_id)
    {
    case 1:
      interface = g_value_get_object (value);
      if (interface != NULL)
        {
          g_warn_if_fail (GOA_REALM_IS_PROVIDER (interface));
          g_dbus_object_skeleton_add_interface (G_DBUS_OBJECT_SKELETON (object), interface);
        }
      else
        {
          g_dbus_object_skeleton_remove_interface_by_name (G_DBUS_OBJECT_SKELETON (object), "org.freedesktop.realmd.Provider");
        }
      break;

    case 2:
      interface = g_value_get_object (value);
      if (interface != NULL)
        {
          g_warn_if_fail (GOA_REALM_IS_SERVICE (interface));
          g_dbus_object_skeleton_add_interface (G_DBUS_OBJECT_SKELETON (object), interface);
        }
      else
        {
          g_dbus_object_skeleton_remove_interface_by_name (G_DBUS_OBJECT_SKELETON (object), "org.freedesktop.realmd.Service");
        }
      break;

    case 3:
      interface = g_value_get_object (value);
      if (interface != NULL)
        {
          g_warn_if_fail (GOA_REALM_IS_COMMON (interface));
          g_dbus_object_skeleton_add_interface (G_DBUS_OBJECT_SKELETON (object), interface);
        }
      else
        {
          g_dbus_object_skeleton_remove_interface_by_name (G_DBUS_OBJECT_SKELETON (object), "org.freedesktop.realmd.Realm");
        }
      break;

    case 4:
      interface = g_value_get_object (value);
      if (interface != NULL)
        {
          g_warn_if_fail (GOA_REALM_IS_KERBEROS (interface));
          g_dbus_object_skeleton_add_interface (G_DBUS_OBJECT_SKELETON (object), interface);
        }
      else
        {
          g_dbus_object_skeleton_remove_interface_by_name (G_DBUS_OBJECT_SKELETON (object), "org.freedesktop.realmd.Kerberos");
        }
      break;

    case 5:
      interface = g_value_get_object (value);
      if (interface != NULL)
        {
          g_warn_if_fail (GOA_REALM_IS_KERBEROS_MEMBERSHIP (interface));
          g_dbus_object_skeleton_add_interface (G_DBUS_OBJECT_SKELETON (object), interface);
        }
      else
        {
          g_dbus_object_skeleton_remove_interface_by_name (G_DBUS_OBJECT_SKELETON (object), "org.freedesktop.realmd.KerberosMembership");
        }
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
      break;
  }
}
