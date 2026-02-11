_clutter_input_device_add_axis (ClutterInputDevice *device,
                                ClutterInputAxis    axis,
                                gdouble             minimum,
                                gdouble             maximum,
                                gdouble             resolution)
{
  ClutterAxisInfo info;
  guint pos;

  if (device->axes == NULL)
    device->axes = g_array_new (FALSE, TRUE, sizeof (ClutterAxisInfo));

  info.axis = axis;
  info.min_value = minimum;
  info.max_value = maximum;
  info.resolution = resolution;

  switch (axis)
    {
    case CLUTTER_INPUT_AXIS_X:
    case CLUTTER_INPUT_AXIS_Y:
      info.min_axis = 0;
      info.max_axis = 0;
      break;

    case CLUTTER_INPUT_AXIS_XTILT:
    case CLUTTER_INPUT_AXIS_YTILT:
      info.min_axis = -1;
      info.max_axis = 1;
      break;

    default:
      info.min_axis = 0;
      info.max_axis = 1;
      break;
    }

  device->axes = g_array_append_val (device->axes, info);
  pos = device->axes->len - 1;

  g_object_notify_by_pspec (G_OBJECT (device), obj_props[PROP_N_AXES]);

  return pos;
}
