drive_does_not_detect_media_change (UDisksLinuxBlockObject *object)
{
  gboolean ret = FALSE;
  UDisksObject *drive_object;

  drive_object = udisks_daemon_find_object (object->daemon, udisks_block_get_drive (object->iface_block_device));
  if (drive_object != NULL)
    {
      UDisksDrive *drive = udisks_object_get_drive (drive_object);
      if (drive != NULL)
        {
          ret = ! udisks_drive_get_media_change_detected (drive);
          g_object_unref (drive);
        }
      g_object_unref (drive_object);
    }
  return ret;
}
