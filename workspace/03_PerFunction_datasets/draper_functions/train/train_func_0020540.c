atom_data_new_from_gst_buffer (guint32 fourcc, const GstBuffer * buf)
{
  AtomData *data = atom_data_new (fourcc);

  atom_data_alloc_mem (data, GST_BUFFER_SIZE (buf));
  g_memmove (data->data, GST_BUFFER_DATA (buf), GST_BUFFER_SIZE (buf));
  return data;
}
