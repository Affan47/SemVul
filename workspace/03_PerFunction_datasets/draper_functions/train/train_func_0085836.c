net_device_get_find_connection (NetDevice *device)
{
        GSList *list, *iterator;
        NMConnection *connection = NULL;
        NMActiveConnection *ac;
        NMRemoteSettings *remote_settings;


        remote_settings = net_object_get_remote_settings (NET_OBJECT (device));
        ac = nm_device_get_active_connection (device->priv->nm_device);
        if (ac) {
                return (NMConnection*)nm_remote_settings_get_connection_by_path (remote_settings,
                                        nm_active_connection_get_connection (ac));
        }


        list = valid_connections_for_device (remote_settings, device);
        if (list != NULL) {

                if (g_slist_length (list) == 1) {
                        connection = list->data;
                        goto out;
                }


                for (iterator = list; iterator; iterator = iterator->next) {
                        connection = iterator->data;
                        if (compare_mac_device_with_mac_connection (device->priv->nm_device,
                                                                    connection)) {
                                goto out;
                        }
                }
        }


        connection = NULL;
out:
        g_slist_free (list);
        return connection;
}
