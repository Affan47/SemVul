mute_stream (GstPad * pad, GstBuffer * buf, gpointer data)
{
  GstStreamInfo *info = GST_STREAM_INFO (data);
  guint id;

  GST_DEBUG ("mute stream triggered");

  g_object_set (G_OBJECT (info), "mute", TRUE, NULL);
  id = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (info), "mute_probe"));
  g_object_set_data (G_OBJECT (info), "mute_probe", NULL);
  if (id > 0)
    gst_pad_remove_buffer_probe (GST_PAD_CAST (info->object), id);


  return FALSE;
}
