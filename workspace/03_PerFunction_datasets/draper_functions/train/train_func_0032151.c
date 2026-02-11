clutter_device_manager_x11_constructed (GObject *gobject)
{
  ClutterDeviceManagerX11 *manager_x11;
  ClutterBackendX11 *backend_x11;

  manager_x11 = CLUTTER_DEVICE_MANAGER_X11 (gobject);

  g_object_get (gobject, "backend", &backend_x11, NULL);
  g_assert (backend_x11 != NULL);

  manager_x11->core_pointer =
    g_object_new (CLUTTER_TYPE_INPUT_DEVICE_X11,
                  "name", "Core Pointer",
                  "has-cursor", TRUE,
                  "device-type", CLUTTER_POINTER_DEVICE,
                  "device-manager", manager_x11,
                  "device-mode", CLUTTER_INPUT_MODE_MASTER,
                  "backend", backend_x11,
                  "enabled", TRUE,
                  NULL);
  CLUTTER_NOTE (BACKEND, "Added core pointer device");

  manager_x11->core_keyboard =
    g_object_new (CLUTTER_TYPE_INPUT_DEVICE_X11,
                  "name", "Core Keyboard",
                  "has-cursor", FALSE,
                  "device-type", CLUTTER_KEYBOARD_DEVICE,
                  "device-manager", manager_x11,
                  "device-mode", CLUTTER_INPUT_MODE_MASTER,
                  "backend", backend_x11,
                  "enabled", TRUE,
                  NULL);
  CLUTTER_NOTE (BACKEND, "Added core keyboard device");


  _clutter_input_device_set_associated_device (manager_x11->core_pointer,
                                               manager_x11->core_keyboard);
  _clutter_input_device_set_associated_device (manager_x11->core_keyboard,
                                               manager_x11->core_pointer);

  if (G_OBJECT_CLASS (clutter_device_manager_x11_parent_class)->constructed)
    G_OBJECT_CLASS (clutter_device_manager_x11_parent_class)->constructed (gobject);
}
