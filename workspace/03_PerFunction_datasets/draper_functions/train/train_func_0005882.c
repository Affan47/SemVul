udisks_linux_drive_object_constructor (GType                  type,
                                       guint                  n_construct_properties,
                                       GObjectConstructParam *construct_properties)
{
  GObjectConstructParam *cp;
  UDisksDaemon *daemon;
  GUdevClient *client;
  UDisksLinuxDevice *device;

  cp = find_construct_property (n_construct_properties, construct_properties, "daemon");
  g_assert (cp != NULL);
  daemon = UDISKS_DAEMON (g_value_get_object (cp->value));
  g_assert (daemon != NULL);

  client = udisks_linux_provider_get_udev_client (udisks_daemon_get_linux_provider (daemon));

  cp = find_construct_property (n_construct_properties, construct_properties, "device");
  g_assert (cp != NULL);
  device = g_value_get_object (cp->value);
  g_assert (device != NULL);

  if (!udisks_linux_drive_object_should_include_device (client, device, NULL))
    {
      return NULL;
    }
  else
    {
      return G_OBJECT_CLASS (udisks_linux_drive_object_parent_class)->constructor (type,
                                                                                   n_construct_properties,
                                                                                   construct_properties);
    }
}
