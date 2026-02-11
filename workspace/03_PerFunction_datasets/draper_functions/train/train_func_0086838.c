unmount_all_with_scheme (const char *scheme)
{
  GVolumeMonitor *volume_monitor;
  GList *mounts;
  GList *l;

  volume_monitor = g_volume_monitor_get();


  iterate_gmain();

  mounts = g_volume_monitor_get_mounts (volume_monitor);
  for (l = mounts; l != NULL; l = l->next) {
    GMount *mount = G_MOUNT (l->data);
    GFile *root;

    root = g_mount_get_root (mount);
    if (g_file_has_uri_scheme (root, scheme)) {
            unmount (root);
    }
    g_object_unref (root);
  }
  g_list_free_full (mounts, g_object_unref);

  g_object_unref (volume_monitor);
}
