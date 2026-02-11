network_device_up (NetworkInterface *device)
{
        if (device->flags & NETWORK_INTERFACE_UP)
                return;

        device->flags |= NETWORK_INTERFACE_UP;

        if (g_hash_table_size (device->contexts) > 0)
                g_hash_table_foreach (device->contexts,
                                      context_signal_up,
                                      device->manager);
        else if (device->flags & NETWORK_INTERFACE_PRECONFIGURED)
                network_device_create_context (device, device->name);
}
