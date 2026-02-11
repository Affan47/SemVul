atspi_accessible_get_child_count (AtspiAccessible *obj, GError **error)
{
  g_return_val_if_fail (obj != NULL, -1);

  if (!_atspi_accessible_test_cache (obj, ATSPI_CACHE_CHILDREN))
  {
    dbus_int32_t ret;
    if (!_atspi_dbus_get_property (obj, atspi_interface_accessible,
                                   "ChildCount", error, "i", &ret))
      return -1;
    return ret;
  }

  return g_list_length (obj->children);
}
