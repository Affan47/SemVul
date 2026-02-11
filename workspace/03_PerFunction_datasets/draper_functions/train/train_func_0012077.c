print_objects (DBusConnection *connection, const char *service_name, const char *cur)
{
  DBusMessage *message;
  DBusMessage *reply;
  DBusError error;
  DBusMessageIter iter;
  const char *introspection_xml;
  NodeInfo *root;
  GSList *nodes;
  GSList *l;

  if (cur == NULL)
    cur = "/";

  message = dbus_message_new_method_call (service_name,
                                          cur,
                                          DBUS_INTERFACE_INTROSPECTABLE,
                                          "Introspect");
  dbus_error_init (&error);
  reply = dbus_connection_send_with_reply_and_block (connection,
                                                     message,
                                                     -1,
                                                     &error);
  dbus_message_unref (message);
  dbus_message_iter_init (reply, &iter);
  dbus_message_iter_get_basic (&iter, &introspection_xml);

  root = description_load_from_string (introspection_xml, strlen (introspection_xml), NULL);
  nodes = node_info_get_nodes (root);

  if (g_slist_length (node_info_get_interfaces (root)) > 0)
    printf ("%s \n", cur);

  for (l = nodes; l != NULL; l = l->next)
    {
      NodeInfo *node = (NodeInfo *) l->data;
      const char *name;
      char *new_path;

      name = node_info_get_name (node);
      if (strcmp (cur, "/") == 0)
        new_path = g_strdup_printf ("/%s", name);
      else
        new_path = g_strdup_printf ("%s/%s", cur, name);

      print_objects (connection, service_name, new_path);

      g_free (new_path);
    }
  node_info_unref (root);

  dbus_message_unref (reply);
}
