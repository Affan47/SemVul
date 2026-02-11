is_keyframe (GstBuffer * buf)
{
  gsize size;
  guint8 data[1];

  size = gst_buffer_get_size (buf);
  if (size == 0)
    return FALSE;

  gst_buffer_extract (buf, 0, data, 1);

  return ((data[0] & 0x40) == 0);
}
