mount_point_matches_mount_entry (GUnixMountPoint *mount_point,
                                 GUnixMountEntry *mount_entry)
{
  gboolean ret = FALSE;
  gchar *mp_path = NULL;
  gchar *mp_entry = NULL;

  mp_path = g_strdup (g_unix_mount_point_get_mount_path (mount_point));
  mp_entry = g_strdup (g_unix_mount_get_mount_path (mount_entry));

  if (g_str_has_suffix (mp_path, "/"))
    mp_path[strlen(mp_path) - 1] = '\0';
  if (g_str_has_suffix (mp_entry, "/"))
    mp_entry[strlen(mp_entry) - 1] = '\0';

  if (g_strcmp0 (mp_path, mp_entry) != 0)
    goto out;

  ret = TRUE;

 out:
  g_free (mp_path);
  g_free (mp_entry);
  return ret;
}
