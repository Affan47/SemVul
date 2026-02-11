have_udisks_volume_for_mount_point (GVfsUDisks2VolumeMonitor *monitor,
                                    GUnixMountPoint          *mount_point)
{
  gboolean ret = FALSE;

  if (find_volume_for_device (monitor, g_unix_mount_point_get_device_path (mount_point)) == NULL)
    goto out;

  ret = TRUE;

 out:
  return ret;
}
