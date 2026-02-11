tp_list_connection_names_helper (TpDBusDaemon *bus_daemon,
                                 const gchar * const *names,
                                 const GError *error,
                                 gpointer user_data,
                                 GObject *user_object)
{
  _ListContext *list_context = user_data;
  const gchar * const *iter;

  GPtrArray *bus_names;

  GPtrArray *cms;

  GPtrArray *protocols;

  if (error != NULL)
    {
      list_context->callback (NULL, 0, NULL, NULL, error,
          list_context->user_data, user_object);
      return;
    }

  bus_names = g_ptr_array_new ();
  cms = g_ptr_array_new ();
  protocols = g_ptr_array_new ();

  for (iter = names; iter != NULL && *iter != NULL; iter++)
    {
      gchar *proto, *cm_name;

      if (_tp_connection_parse (*iter, '.', &proto, &cm_name))
        {


          g_ptr_array_add (bus_names, (gpointer) *iter);
          g_ptr_array_add (cms, cm_name);
          g_ptr_array_add (protocols, proto);
          continue;
        }
    }

  g_ptr_array_add (bus_names, NULL);
  g_ptr_array_add (cms, NULL);
  g_ptr_array_add (protocols, NULL);

  list_context->callback ((const gchar * const *) bus_names->pdata,
      bus_names->len - 1, (const gchar * const *) cms->pdata,
      (const gchar * const *) protocols->pdata,
      NULL, list_context->user_data, user_object);

  g_ptr_array_unref (bus_names);
  g_strfreev ((char **) g_ptr_array_free (cms, FALSE));
  g_strfreev ((char **) g_ptr_array_free (protocols, FALSE));
}
