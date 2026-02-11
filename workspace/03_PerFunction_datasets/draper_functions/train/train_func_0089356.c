marshal_object (DBusMessageIter         *iter,
		const GValue            *value)
{
  const char *path;
  GObject *obj;

  obj = g_value_get_object (value);
  g_return_val_if_fail (G_IS_OBJECT (obj), FALSE);

  path = _dbus_gobject_get_path (obj);
  g_return_val_if_fail (g_variant_is_object_path (path), FALSE);

  if (!dbus_message_iter_append_basic (iter,
				       DBUS_TYPE_OBJECT_PATH,
				       &path))
    oom ();

  return TRUE;
}
