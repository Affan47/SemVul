name_owner_changed (DBusGProxy *proxy,
                    const char *name,
                    const char *prev_owner,
                    const char *new_owner,
                    gpointer user_data)
{


  if (new_owner[0] == '\0' && strcmp (name, prev_owner) == 0) {
    GList *list;

    list = g_hash_table_lookup (clients, prev_owner);
    SW_DEBUG (CLIENT_MONITOR, "Client %s went away. It was using %d objects",
              name,
              g_list_length (list));
    g_hash_table_remove (clients, prev_owner);

    while (list) {
      g_object_unref (list->data);
      list = g_list_delete_link (list, list);
    }
  }
}
