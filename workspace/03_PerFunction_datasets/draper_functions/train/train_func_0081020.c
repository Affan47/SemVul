is_supported (GProxyVolumeMonitorClass *klass)
{
  gboolean res;

  G_LOCK (proxy_vm);
  res = g_proxy_volume_monitor_setup_session_bus_connection ();
  G_UNLOCK (proxy_vm);

  if (res)
    res = is_remote_monitor_supported (klass->dbus_name);

  return res;
}
