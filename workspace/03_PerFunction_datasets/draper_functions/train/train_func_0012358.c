e_dbus_object_free(E_DBus_Object *obj)
{
  E_DBus_Interface *iface;

  if (!obj) return;

  DBG("e_dbus_object_free (%s)", obj->path);
  dbus_connection_unregister_object_path(obj->conn->conn, obj->path);
  e_dbus_connection_close(obj->conn);

  if (obj->path) free(obj->path);
  EINA_LIST_FREE(obj->interfaces, iface)
    e_dbus_interface_unref(iface);

  if (obj->introspection_data) free(obj->introspection_data);

  free(obj);
}
