gst_buffer_fill (GstBuffer * buffer, gsize offset, gconstpointer src,
    gsize size)
{
  gsize i, len, left;
  const guint8 *ptr = src;

  g_return_val_if_fail (GST_IS_BUFFER (buffer), 0);
  g_return_val_if_fail (gst_buffer_is_writable (buffer), 0);
  g_return_val_if_fail (src != NULL || size == 0, 0);

  GST_CAT_LOG (GST_CAT_BUFFER,
      "buffer %p, offset %" G_GSIZE_FORMAT ", size %" G_GSIZE_FORMAT, buffer,
      offset, size);

  len = GST_BUFFER_MEM_LEN (buffer);
  left = size;

  for (i = 0; i < len && left > 0; i++) {
    GstMapInfo info;
    gsize tocopy;
    GstMemory *mem;

    mem = _get_mapped (buffer, i, &info, GST_MAP_WRITE);
    if (info.size > offset) {

      tocopy = MIN (info.size - offset, left);
      memcpy ((guint8 *) info.data + offset, ptr, tocopy);
      left -= tocopy;
      ptr += tocopy;
      offset = 0;
    } else {

      offset -= info.size;
    }
    gst_memory_unmap (mem, &info);
  }
  return size - left;
}
