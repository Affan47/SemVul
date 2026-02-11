gst_buffer_append_region (GstBuffer * buf1, GstBuffer * buf2, gssize offset,
    gssize size)
{
  gsize i, len;

  g_return_val_if_fail (GST_IS_BUFFER (buf1), NULL);
  g_return_val_if_fail (GST_IS_BUFFER (buf2), NULL);

  buf1 = gst_buffer_make_writable (buf1);
  buf2 = gst_buffer_make_writable (buf2);

  gst_buffer_resize (buf2, offset, size);

  len = GST_BUFFER_MEM_LEN (buf2);
  for (i = 0; i < len; i++) {
    GstMemory *mem;

    mem = GST_BUFFER_MEM_PTR (buf2, i);
    GST_BUFFER_MEM_PTR (buf2, i) = NULL;
    _memory_add (buf1, -1, mem, FALSE);
  }

  GST_BUFFER_MEM_LEN (buf2) = 0;
  gst_buffer_unref (buf2);

  return buf1;
}
