atspi_accessible_get_attributes_as_array (AtspiAccessible *obj, GError **error)
{
  DBusMessage *message;

    g_return_val_if_fail (obj != NULL, NULL);

  if (_atspi_accessible_get_cache_mask (obj) & ATSPI_CACHE_ATTRIBUTES)
  {
    GArray *array = g_array_new (TRUE, TRUE, sizeof (gchar *));
    GHashTable *attributes = atspi_accessible_get_attributes (obj, error);
    if (!attributes)
      return NULL;
    g_hash_table_foreach (attributes, add_to_attribute_array, &array);
    g_hash_table_unref (attributes);
    return array;
  }

  message = _atspi_dbus_call_partial (obj, atspi_interface_accessible, "GetAttributes", error, "");
  return _atspi_dbus_return_attribute_array_from_message (message);
}
