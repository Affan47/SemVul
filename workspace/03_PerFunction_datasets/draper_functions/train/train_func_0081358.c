clutter_device_manager_get_device (ClutterDeviceManager *device_manager,
                                   gint                  device_id)
{
  ClutterDeviceManagerClass *manager_class;

  g_return_val_if_fail (CLUTTER_IS_DEVICE_MANAGER (device_manager), NULL);

  manager_class = CLUTTER_DEVICE_MANAGER_GET_CLASS (device_manager);
  return manager_class->get_device (device_manager, device_id);
}
