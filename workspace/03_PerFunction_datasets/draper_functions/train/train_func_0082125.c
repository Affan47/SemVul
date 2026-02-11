gst_qt_mux_prepare_jpc_buffer (GstQTPad * qtpad, GstBuffer * buf,
    GstQTMux * qtmux)
{
  GstBuffer *newbuf;
  GstMapInfo map;
  gsize size;

  GST_LOG_OBJECT (qtmux, "Preparing jpc buffer");

  if (buf == NULL)
    return NULL;

  size = gst_buffer_get_size (buf);
  newbuf = gst_buffer_new_and_alloc (size + 8);
  gst_buffer_copy_into (newbuf, buf, GST_BUFFER_COPY_ALL, 8, size);

  gst_buffer_map (newbuf, &map, GST_MAP_WRITE);
  GST_WRITE_UINT32_BE (map.data, map.size);
  GST_WRITE_UINT32_LE (map.data + 4, FOURCC_jp2c);

  gst_buffer_unmap (buf, &map);
  gst_buffer_unref (buf);

  return newbuf;
}
