clutter_input_device_get_coords (ClutterInputDevice   *device,
                                 ClutterEventSequence *sequence,
                                 ClutterPoint         *point)
{
  g_return_val_if_fail (CLUTTER_IS_INPUT_DEVICE (device), FALSE);
  g_return_val_if_fail (point != NULL, FALSE);

  if (sequence == NULL)
    {
      point->x = device->current_x;
      point->y = device->current_y;
    }
  else
    {
      ClutterTouchInfo *info =
        g_hash_table_lookup (device->touch_sequences_info, sequence);

      if (info == NULL)
        return FALSE;

      point->x = info->current_x;
      point->y = info->current_y;
    }

  return TRUE;
}
