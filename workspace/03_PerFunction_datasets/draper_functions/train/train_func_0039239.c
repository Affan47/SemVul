g_daemon_volume_monitor_dispose (GObject *object)
{
  G_LOCK (daemon_vm);
  _the_daemon_volume_monitor = NULL;
  G_UNLOCK (daemon_vm);

  if (G_OBJECT_CLASS (g_daemon_volume_monitor_parent_class)->dispose)
    (*G_OBJECT_CLASS (g_daemon_volume_monitor_parent_class)->dispose) (object);
}
