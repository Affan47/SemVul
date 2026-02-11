handle_remove_accessible (DBusConnection *bus, DBusMessage *message, void *user_data)
{
  const char *sender = dbus_message_get_sender (message);
  AtspiApplication *app;
  const char *path;
  DBusMessageIter iter, iter_struct;
  const char *signature = dbus_message_get_signature (message);
  AtspiAccessible *a;

  if (strcmp (signature, "(so)") != 0)
  {
    g_warning ("AT-SPI: Unknown signature %s for RemoveAccessible", signature);
    return DBUS_HANDLER_RESULT_HANDLED;
  }

  dbus_message_iter_init (message, &iter);
  dbus_message_iter_recurse (&iter, &iter_struct);
  dbus_message_iter_get_basic (&iter_struct, &sender);
  dbus_message_iter_next (&iter_struct);
  dbus_message_iter_get_basic (&iter_struct, &path);
  app = get_application (sender);
  a = ref_accessible (sender, path);
  if (!a)
    return DBUS_HANDLER_RESULT_HANDLED;
  g_object_run_dispose (G_OBJECT (a));
  g_hash_table_remove (app->hash, a->parent.path);
  g_object_unref (a);
  return DBUS_HANDLER_RESULT_HANDLED;
}
