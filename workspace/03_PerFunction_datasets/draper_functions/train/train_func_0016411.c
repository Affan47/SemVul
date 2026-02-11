gst_buffer_remove_memory_range (GstBuffer * buffer, guint idx, gint length)
{
  guint len;

  g_return_if_fail (GST_IS_BUFFER (buffer));
  g_return_if_fail (gst_buffer_is_writable (buffer));

  GST_CAT_DEBUG (GST_CAT_BUFFER, "idx %u, length %d", idx, length);

  len = GST_BUFFER_MEM_LEN (buffer);
  g_return_if_fail ((len == 0 && idx == 0 && length == -1) ||
      (length == -1 && idx < len) || length + idx <= len);

  if (length == -1)
    length = len - idx;

  _replace_memory (buffer, len, idx, length, NULL);
}
