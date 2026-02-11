empathy_camera_device_monitor_finalize (GObject *object)
{
#ifdef HAVE_UDEV
  EmpathyCameraDeviceMonitor *monitor = EMPATHY_CAMERA_DEVICE_MONITOR (object);
  EmpathyCameraDeviceMonitorPrivate *priv = EMPATHY_CAMERA_DEVICE_MONITOR_GET_PRIVATE (monitor);

  if (priv->client != NULL)
  {
    g_object_unref (priv->client);
    priv->client = NULL;
  }
#endif
  G_OBJECT_CLASS (empathy_camera_device_monitor_parent_class)->finalize (object);
}
