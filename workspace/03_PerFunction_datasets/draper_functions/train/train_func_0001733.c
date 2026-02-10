clutter_input_device_get_device_coords (ClutterInputDevice *device,
                                        gint               *x,
                                        gint               *y)
{
  ClutterPoint point;

  clutter_input_device_get_coords (device, NULL, &point);

  if (x)
    *x = point.x;

  if (y)
    *y = point.y;
}
