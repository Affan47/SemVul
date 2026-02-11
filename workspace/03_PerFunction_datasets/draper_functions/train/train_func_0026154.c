gvfs_udisks2_volume_monitor_dispose (GObject *object)
{
  the_volume_monitor = NULL;

  if (G_OBJECT_CLASS (gvfs_udisks2_volume_monitor_parent_class)->dispose != NULL)
    G_OBJECT_CLASS (gvfs_udisks2_volume_monitor_parent_class)->dispose (object);
}
