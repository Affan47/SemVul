ignore_volume (GVolume *volume)
{
  gboolean ret = TRUE;
  char *path;
  GDrive *drive;


  drive = g_volume_get_drive (volume);
  if (drive != NULL && ignore_drive (drive)) {
    g_object_unref (drive);
    return TRUE;
  }
  g_clear_object (&drive);

  path = g_volume_get_identifier (volume, G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE);

  if (path != NULL) {
    ret = FALSE;
    g_free (path);
  } else {
    GRL_DEBUG ("%s: Not adding volume %s as it has no identifier", __FUNCTION__,
               g_volume_get_name (volume));
  }

  return ret;
}
