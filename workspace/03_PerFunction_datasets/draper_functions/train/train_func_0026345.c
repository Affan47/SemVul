udisks_mount_monitor_get_mounts_for_dev (UDisksMountMonitor *monitor,
                                         dev_t               dev)
{
  GList *ret;
  GList *l;

  ret = NULL;

  udisks_mount_monitor_ensure (monitor);

  for (l = monitor->mounts; l != NULL; l = l->next)
    {
      UDisksMount *mount = UDISKS_MOUNT (l->data);

      if (udisks_mount_get_dev (mount) == dev)
        {
          ret = g_list_prepend (ret, g_object_ref (mount));
        }
    }


  ret = g_list_sort (ret, (GCompareFunc) udisks_mount_compare);

  return ret;
}
