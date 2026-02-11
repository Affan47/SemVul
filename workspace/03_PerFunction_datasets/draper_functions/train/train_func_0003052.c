add_accessible_from_iter (DBusMessageIter *iter)
{
  DBusMessageIter iter_struct, iter_array;
  const char *app_name, *path;
  AtspiAccessible *accessible;
  const char *name, *description;
  dbus_uint32_t role;

  dbus_message_iter_recurse (iter, &iter_struct);


  get_reference_from_iter (&iter_struct, &app_name, &path);
  accessible = ref_accessible (app_name, path);
  if (!accessible)
    return;


  dbus_message_iter_next (&iter_struct);


  get_reference_from_iter (&iter_struct, &app_name, &path);
  if (accessible->accessible_parent)
    g_object_unref (accessible->accessible_parent);
  accessible->accessible_parent = ref_accessible (app_name, path);


  while (accessible->children)
  {
    g_object_unref (accessible->children->data);
    accessible->children = g_list_remove (accessible->children, accessible->children->data);
  }
  dbus_message_iter_recurse (&iter_struct, &iter_array);
  while (dbus_message_iter_get_arg_type (&iter_array) != DBUS_TYPE_INVALID)
  {
    AtspiAccessible *child;
    get_reference_from_iter (&iter_array, &app_name, &path);
    child = ref_accessible (app_name, path);
    accessible->children = g_list_append (accessible->children, child);
  }


  dbus_message_iter_next (&iter_struct);
  _atspi_dbus_set_interfaces (accessible, &iter_struct);
  dbus_message_iter_next (&iter_struct);


  if (accessible->name)
    g_free (accessible->name);
  dbus_message_iter_get_basic (&iter_struct, &name);
  accessible->name = g_strdup (name);
  dbus_message_iter_next (&iter_struct);


  dbus_message_iter_get_basic (&iter_struct, &role);
  accessible->role = role;
  dbus_message_iter_next (&iter_struct);


  if (accessible->description)
    g_free (accessible->description);
  dbus_message_iter_get_basic (&iter_struct, &description);
  accessible->description = g_strdup (description);
  dbus_message_iter_next (&iter_struct);

  _atspi_dbus_set_state (accessible, &iter_struct);
  dbus_message_iter_next (&iter_struct);

  _atspi_accessible_add_cache (accessible, ATSPI_CACHE_NAME | ATSPI_CACHE_ROLE |
                               ATSPI_CACHE_PARENT | ATSPI_CACHE_DESCRIPTION);
  if (!atspi_state_set_contains (accessible->states,
                                       ATSPI_STATE_MANAGES_DESCENDANTS))
    _atspi_accessible_add_cache (accessible, ATSPI_CACHE_CHILDREN);


  g_object_unref (accessible);
}
