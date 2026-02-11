clutter_input_device_get_grabbed_actor (ClutterInputDevice *device)
{
  g_return_val_if_fail (CLUTTER_IS_INPUT_DEVICE (device), NULL);

  switch (device->device_type)
    {
    case CLUTTER_POINTER_DEVICE:
      return device->pointer_grab_actor;

    case CLUTTER_KEYBOARD_DEVICE:
      return device->keyboard_grab_actor;

    default:
      g_critical ("Only pointer and keyboard devices can grab an actor");
    }

  return NULL;
}
