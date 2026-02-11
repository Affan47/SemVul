panel_add_device (CcNetworkPanel *panel, NMDevice *device)
{
        const gchar *title;
        GtkListStore *liststore_devices;
        GtkTreeIter iter;
        NMDeviceType type;
        NetDevice *net_device;
        CcNetworkPanelPrivate *priv = panel->priv;
        GtkNotebook *notebook;
        GtkSizeGroup *size_group;
        GType device_g_type;


        if (find_in_model_by_id (panel, nm_device_get_udi (device)) != NULL)
                goto out;

        type = nm_device_get_device_type (device);

        g_debug ("device %s type %i path %s",
                 nm_device_get_udi (device), type, nm_object_get_path (NM_OBJECT (device)));


        switch (type) {
        case NM_DEVICE_TYPE_ETHERNET:
                device_g_type = NET_TYPE_DEVICE_WIRED;
                break;
        case NM_DEVICE_TYPE_MODEM:
                device_g_type = NET_TYPE_DEVICE_MOBILE;
                break;
        case NM_DEVICE_TYPE_WIFI:
                device_g_type = NET_TYPE_DEVICE_WIFI;
                break;
        default:
                goto out;
        }


        title = panel_device_to_localized_string (device);
        net_device = g_object_new (device_g_type,
                                   "panel", panel,
                                   "removable", FALSE,
                                   "cancellable", panel->priv->cancellable,
                                   "client", panel->priv->client,
                                   "remote-settings", panel->priv->remote_settings,
                                   "nm-device", device,
                                   "id", nm_device_get_udi (device),
                                   "title", title,
                                   NULL);


        if (device_g_type != NET_TYPE_DEVICE) {
                notebook = GTK_NOTEBOOK (gtk_builder_get_object (panel->priv->builder,
                                                                 "notebook_types"));
                size_group = GTK_SIZE_GROUP (gtk_builder_get_object (panel->priv->builder,
                                                                     "sizegroup1"));
                net_object_add_to_notebook (NET_OBJECT (net_device),
                                            notebook,
                                            size_group);
        }

        liststore_devices = GTK_LIST_STORE (gtk_builder_get_object (priv->builder,
                                            "liststore_devices"));
        g_signal_connect_object (net_device, "removed",
                                 G_CALLBACK (object_removed_cb), panel, 0);
        gtk_list_store_append (liststore_devices, &iter);
        gtk_list_store_set (liststore_devices,
                            &iter,
                            PANEL_DEVICES_COLUMN_ICON, panel_device_to_icon_name (device),
                            PANEL_DEVICES_COLUMN_SORT, panel_device_to_sortable_string (device),
                            PANEL_DEVICES_COLUMN_TITLE, title,
                            PANEL_DEVICES_COLUMN_OBJECT, net_device,
                            -1);

out:
        return FALSE;
}
