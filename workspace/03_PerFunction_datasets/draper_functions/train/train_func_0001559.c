clean_up (void)
{
  GdkWindow *root;
  GdkDeviceManager *dev_manager;
  GdkDevice        *device;
  GList            *devices, *l;

  root = gdk_get_default_root_window ();
  dev_manager = gdk_display_get_device_manager (gdk_display_get_default ());
  gdk_window_remove_filter (root, (GdkFilterFunc) target_filter, NULL);

  device = gdk_device_manager_get_client_pointer (dev_manager);
  gdk_device_ungrab (device, GDK_CURRENT_TIME);

  devices = gdk_device_manager_list_devices (dev_manager, GDK_DEVICE_TYPE_MASTER);

  for (l = devices; l; l = l->next)
    {
      device = GDK_DEVICE (l->data);

      if (gdk_device_get_source (device) != GDK_SOURCE_KEYBOARD)
        continue;

      gdk_device_ungrab (device, GDK_CURRENT_TIME);
    }

  g_list_free (devices);

  gtk_main_quit ();
}
