check_property_access (DBusConnection  *connection,
                       DBusMessage     *message,
                       GObject         *object,
                       const char      *wincaps_propiface,
                       const char      *requested_propname,
                       const char      *uscore_propname,
                       gboolean         is_set)
{
  const DBusGObjectInfo *object_info;
  const char *access_type;
  DBusMessage *ret;
  gchar *error_message;

  if (!is_set && !disable_legacy_property_access)
    return TRUE;

  object_info = lookup_object_info_by_iface (object, wincaps_propiface, TRUE, NULL);
  if (!object_info)
    {
      error_message = g_strdup_printf (
          "Interface \"%s\" isn't exported (or may not exist), can't access property \"%s\"",
          wincaps_propiface, requested_propname);

      goto error;
    }


  if (object_info
      && !(property_info_from_object_info (object_info, wincaps_propiface, requested_propname, &access_type)
           || property_info_from_object_info (object_info, wincaps_propiface, uscore_propname, &access_type)))
    {
      error_message = g_strdup_printf (
          "Property \"%s\" of interface \"%s\" isn't exported (or may not exist)",
          requested_propname, wincaps_propiface);

      goto error;
    }

  if (strcmp (access_type, "readwrite") == 0)
    return TRUE;

  if (is_set ? strcmp (access_type, "read") == 0
             : strcmp (access_type, "write") == 0)
    {
      error_message = g_strdup_printf (
          "Property \"%s\" of interface \"%s\" is not %s",
          requested_propname,
          wincaps_propiface,
          is_set ? "settable" : "readable");

      goto error;
    }

  return TRUE;

error:
  ret = error_or_die (message, DBUS_ERROR_ACCESS_DENIED, error_message);
  g_free (error_message);

  connection_send_or_die (connection, ret);
  dbus_message_unref (ret);
  return FALSE;
}
