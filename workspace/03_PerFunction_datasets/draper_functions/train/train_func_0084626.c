mount_with_device_file (const char *device_file)
{
  GVolumeMonitor *volume_monitor;
  GList *volumes;
  GList *l;

  volume_monitor = g_volume_monitor_get();

  volumes = g_volume_monitor_get_volumes (volume_monitor);
  for (l = volumes; l != NULL; l = l->next)
    {
      GVolume *volume = G_VOLUME (l->data);

      if (g_strcmp0 (g_volume_get_identifier (volume,
                                              G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE), device_file) == 0)
        {
          GMountOperation *op;

          op = new_mount_op ();

          g_volume_mount (volume,
                          G_MOUNT_MOUNT_NONE,
                          op,
                          NULL,
                          mount_with_device_file_cb,
                          op);

          outstanding_mounts++;
        }
    }
  g_list_free_full (volumes, g_object_unref);

  if (outstanding_mounts == 0)
    {
      g_print (_("No volume for device file %s\n"), device_file);
      return;
    }

  g_object_unref (volume_monitor);
}
