cheese_camera_device_find_full_format (CheeseCameraDevice *device,
                                       CheeseVideoFormat* format)
{
  GList *l;

  for (l = device->priv->formats; l != NULL; l = g_list_next (l))
  {
    CheeseVideoFormatFull *item = l->data;

    if ((item != NULL) &&
        (item->width == format->width) && (item->height == format->height))
    {
      return item;
    }
  }

  return NULL;
}
