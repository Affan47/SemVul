evd_dbus_agent_find_proxy_data_by_proxy (ObjectData *data,
                                         GDBusProxy *proxy,
                                         guint      *proxy_id)
{
  ProxyData *proxy_data;
  GHashTableIter iter;
  gpointer key, value;

  g_hash_table_iter_init (&iter, data->proxies);
  while (g_hash_table_iter_next (&iter, &key, &value))
    {
      proxy_data = (ProxyData *) value;

      if (proxy_data->proxy == proxy)
        {
          *proxy_id = * (guint *) key;
          return proxy_data;
        }
    }

  return NULL;
}
