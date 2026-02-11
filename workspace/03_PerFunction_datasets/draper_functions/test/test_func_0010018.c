update_iface (UDisksLinuxMDRaidObject   *object,
              const gchar              *uevent_action,
              HasInterfaceFunc          has_func,
              ConnectInterfaceFunc      connect_func,
              UpdateInterfaceFunc       update_func,
              GType                     skeleton_type,
              gpointer                  _interface_pointer)
{
  gboolean ret = FALSE;
  gboolean has;
  gboolean add;
  GDBusInterface **interface_pointer = _interface_pointer;

  g_return_val_if_fail (object != NULL, FALSE);
  g_return_val_if_fail (has_func != NULL, FALSE);
  g_return_val_if_fail (update_func != NULL, FALSE);
  g_return_val_if_fail (g_type_is_a (skeleton_type, G_TYPE_OBJECT), FALSE);
  g_return_val_if_fail (g_type_is_a (skeleton_type, G_TYPE_DBUS_INTERFACE), FALSE);
  g_return_val_if_fail (interface_pointer != NULL, FALSE);
  g_return_val_if_fail (*interface_pointer == NULL || G_IS_DBUS_INTERFACE (*interface_pointer), FALSE);

  add = FALSE;
  has = has_func (object);
  if (*interface_pointer == NULL)
    {
      if (has)
        {
          *interface_pointer = g_object_new (skeleton_type, NULL);
          if (connect_func != NULL)
            connect_func (object);
          add = TRUE;
        }
    }
  else
    {
      if (!has)
        {
          g_dbus_object_skeleton_remove_interface (G_DBUS_OBJECT_SKELETON (object),
                                                   G_DBUS_INTERFACE_SKELETON (*interface_pointer));
          g_object_unref (*interface_pointer);
          *interface_pointer = NULL;
        }
    }

  if (*interface_pointer != NULL)
    {
      if (update_func (object, uevent_action, G_DBUS_INTERFACE (*interface_pointer)))
        ret = TRUE;
      if (add)
        g_dbus_object_skeleton_add_interface (G_DBUS_OBJECT_SKELETON (object),
                                              G_DBUS_INTERFACE_SKELETON (*interface_pointer));
    }

  return ret;
}
