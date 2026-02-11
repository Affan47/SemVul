gvfs_udisks2_drive_set_volume (GVfsUDisks2Drive  *drive,
                               GVfsUDisks2Volume *volume)
{
  if (g_list_find (drive->volumes, volume) == NULL)
    {
      drive->volumes = g_list_prepend (drive->volumes, volume);
      emit_changed (drive);
    }
}
