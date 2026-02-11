get_connected_drives (GVolumeMonitor *volume_monitor)
{
  GProxyVolumeMonitor *monitor;
  GList *l;
  GHashTableIter hash_iter;
  GProxyDrive *drive;

  monitor = G_PROXY_VOLUME_MONITOR (volume_monitor);
  l = NULL;

  G_LOCK (proxy_vm);

  g_hash_table_iter_init (&hash_iter, monitor->drives);
  while (g_hash_table_iter_next (&hash_iter, NULL, (gpointer) &drive))
    l = g_list_append (l, g_object_ref (drive));

  G_UNLOCK (proxy_vm);

  l = g_list_sort (l, (GCompareFunc) drive_compare);

  return l;
}
