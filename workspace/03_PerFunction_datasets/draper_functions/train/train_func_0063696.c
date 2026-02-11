gvfs_udisks2_volume_unset_drive (GVfsUDisks2Volume *volume,
                                 GVfsUDisks2Drive  *drive)
{
  if (volume->drive == drive)
    {
      volume->drive = NULL;
      emit_changed (volume);
    }
}
