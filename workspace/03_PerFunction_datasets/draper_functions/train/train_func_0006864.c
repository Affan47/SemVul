entangle_device_manager_init_devices(EntangleDeviceManager *manager)
{
    EntangleDeviceManagerPrivate *priv = manager->priv;
    GList *devs, *tmp;
    const gchar *const subsys[] = {
        "usb/usb_device", NULL,
    };

    ENTANGLE_DEBUG("Init udev");

    priv->ctx = g_udev_client_new(subsys);

    g_signal_connect(priv->ctx, "uevent", G_CALLBACK(do_udev_event), manager);

    devs = g_udev_client_query_by_subsystem(priv->ctx, "usb");

    tmp = devs;
    while (tmp) {
        GUdevDevice *dev = tmp->data;

        do_udev_event(priv->ctx, "add", dev, manager);

        g_object_unref(dev);
        tmp = tmp->next;
    }

    g_list_free(devs);
}
