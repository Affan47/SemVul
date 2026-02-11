union_monitor_mount_changed (GVolumeMonitor *union_monitor,
                             GMount         *mount,
                             GProxyVolume   *volume)
{
  if (volume->shadow_mount != NULL)
    {
      GMount *real_mount;
      real_mount = g_proxy_shadow_mount_get_real_mount (volume->shadow_mount);
      if (mount == real_mount)
        {
          signal_emit_in_idle (volume->shadow_mount, "changed", NULL);
          signal_emit_in_idle (volume->volume_monitor, "mount-changed", volume->shadow_mount);
        }
      g_object_unref (real_mount);
    }
}
