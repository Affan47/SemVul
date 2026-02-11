mx_image_async_data_new (MxImage *parent)
{
  MxImageAsyncData *data = g_new0 (MxImageAsyncData, 1);

  data->parent = parent;
  data->mutex = g_mutex_new ();
  data->width = -1;
  data->height = -1;
  data->upscale = parent->priv->upscale;
  data->width_threshold = parent->priv->width_threshold;
  data->height_threshold = parent->priv->height_threshold;

  return data;
}
