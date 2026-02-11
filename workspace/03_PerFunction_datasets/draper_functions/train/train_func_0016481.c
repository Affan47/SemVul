proxy_new(GDBusClient *client, const char *path,
						const char *interface)
{
	GDBusProxy *proxy;

	proxy = g_try_new0(GDBusProxy, 1);
	if (proxy == NULL)
		return NULL;

	proxy->client = client;
	proxy->obj_path = g_strdup(path);
	proxy->interface = g_strdup(interface);

	proxy->prop_list = g_hash_table_new_full(g_str_hash, g_str_equal,
							NULL, prop_entry_free);

	proxy->match_rule = g_strdup_printf("type='signal',"
				"sender='%s',path='%s',interface='%s',"
				"member='PropertiesChanged',arg0='%s'",
				client->service_name, proxy->obj_path,
				DBUS_INTERFACE_PROPERTIES, proxy->interface);

	modify_match(client->dbus_conn, "AddMatch", proxy->match_rule);

	return g_dbus_proxy_ref(proxy);
}
