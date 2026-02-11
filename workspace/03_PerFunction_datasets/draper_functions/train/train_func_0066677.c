marshal_object_path (DBusMessageIter         *iter,
		     const GValue            *value)
{
  const char *path;

  g_assert (G_VALUE_TYPE (value) == DBUS_TYPE_G_OBJECT_PATH);

  path = g_value_get_boxed (value);
  g_return_val_if_fail (g_variant_is_object_path (path), FALSE);

  if (!dbus_message_iter_append_basic (iter,
				       DBUS_TYPE_OBJECT_PATH,
				       &path))
    oom ();

  return TRUE;
}
