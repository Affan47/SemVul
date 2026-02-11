network_device_new (GUPnPLinuxContextManager *manager,
                    int                       index)
{
        NetworkInterface *device;
        struct ifreq ifr;
        int ret;


        memset (&ifr, 0, sizeof (struct ifreq));
        ifr.ifr_ifindex = index;
        ret = ioctl (manager->priv->fd, SIOCGIFNAME, &ifr);

        if (ret == -1) {
                g_warning ("Could not get interface name for index %d",
                           index);

                return NULL;
        }

        device = g_slice_new0 (NetworkInterface);
        device->manager = manager;
        device->name = g_strdup (ifr.ifr_name);

        device->contexts = g_hash_table_new_full (g_str_hash,
                                                  g_str_equal,
                                                  g_free,
                                                  g_object_unref);

        return device;
}
