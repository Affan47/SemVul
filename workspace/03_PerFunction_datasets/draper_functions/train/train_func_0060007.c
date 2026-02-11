cheese_camera_device_monitor_class_init (CheeseCameraDeviceMonitorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  if (cheese_device_monitor_cat == NULL)
    GST_DEBUG_CATEGORY_INIT (cheese_device_monitor_cat,
                             "cheese-device-monitor",
                             0, "Cheese Camera Device Monitor");

  object_class->finalize = cheese_camera_device_monitor_finalize;


  monitor_signals[ADDED] = g_signal_new ("added", G_OBJECT_CLASS_TYPE (klass),
                                         G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                                         G_STRUCT_OFFSET (CheeseCameraDeviceMonitorClass, added),
                                         NULL, NULL,
                                         g_cclosure_marshal_VOID__OBJECT,
                                         G_TYPE_NONE, 1, CHEESE_TYPE_CAMERA_DEVICE);


  monitor_signals[REMOVED] = g_signal_new ("removed", G_OBJECT_CLASS_TYPE (klass),
                                           G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                                           G_STRUCT_OFFSET (CheeseCameraDeviceMonitorClass, removed),
                                           NULL, NULL,
                                           g_cclosure_marshal_VOID__STRING,
                                           G_TYPE_NONE, 1, G_TYPE_STRING);

  g_type_class_add_private (klass, sizeof (CheeseCameraDeviceMonitorPrivate));
}
