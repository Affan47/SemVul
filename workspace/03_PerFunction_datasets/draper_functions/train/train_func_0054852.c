gst_buffer_list_new_sized (guint size)
{
  GstBufferList *list;

  list = g_slice_new0 (GstBufferList);

  GST_LOG ("new %p", list);

  gst_buffer_list_init (list, size);

  return list;
}
