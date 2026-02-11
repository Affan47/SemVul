gudev_remove_device (GMtpVolumeMonitor *monitor, GUdevDevice *device)
{
  GList *l, *ll;
  const gchar* sysfs_path;

  sysfs_path = g_udev_device_get_sysfs_path (device);

  g_debug ("gudev_remove_device: %s", g_udev_device_get_device_file (device));

  for (l = monitor->device_volumes; l != NULL; l = ll) {
    GMtpVolume *volume = G_MTP_VOLUME (l->data);

    ll = l->next;

    if (g_mtp_volume_has_path (volume, sysfs_path)) {
      g_debug ("gudev_remove_device: found volume %s, deleting", sysfs_path);
      g_signal_emit_by_name (monitor, "volume_removed", volume);
      g_signal_emit_by_name (volume, "removed");
      g_mtp_volume_removed (volume);
      monitor->device_volumes = g_list_remove (monitor->device_volumes, volume);
      g_object_unref (volume);
    }
  }
}
