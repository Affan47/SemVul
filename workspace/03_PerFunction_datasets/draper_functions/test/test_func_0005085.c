udisks_linux_block_object_new (UDisksDaemon      *daemon,
                               UDisksLinuxDevice *device)
{
  g_return_val_if_fail (UDISKS_IS_DAEMON (daemon), NULL);
  return UDISKS_LINUX_BLOCK_OBJECT (g_object_new (UDISKS_TYPE_LINUX_BLOCK_OBJECT,
                                                  "daemon", daemon,
                                                  "device", device,
                                                  NULL));
}
