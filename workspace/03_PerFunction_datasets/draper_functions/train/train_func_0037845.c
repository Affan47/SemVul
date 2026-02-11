gst_collect_pads_read_buffer (GstCollectPads * pads, GstCollectData * data,
    guint size)
{
  guint readsize, bufsize;
  GstBuffer *buffer;

  g_return_val_if_fail (pads != NULL, NULL);
  g_return_val_if_fail (GST_IS_COLLECT_PADS (pads), NULL);
  g_return_val_if_fail (data != NULL, NULL);


  if ((buffer = data->buffer) == NULL)
    return NULL;

  bufsize = GST_BUFFER_SIZE (buffer);

  readsize = MIN (size, bufsize - data->pos);

  if (data->pos == 0 && readsize == bufsize)
    return gst_buffer_ref (buffer);
  else
    return gst_buffer_create_sub (buffer, data->pos, readsize);
}
