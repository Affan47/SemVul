gst_hls_src_buf_to_utf8_playlist (GstBuffer * buf)
{
  GstMapInfo info;
  gchar *playlist;

  if (!gst_buffer_map (buf, &info, GST_MAP_READ))
    goto map_error;

  if (!g_utf8_validate ((gchar *) info.data, info.size, NULL))
    goto validate_error;


  playlist = g_malloc0 (info.size + 1);
  memcpy (playlist, info.data, info.size);

  gst_buffer_unmap (buf, &info);
  gst_buffer_unref (buf);
  return playlist;

validate_error:
  gst_buffer_unmap (buf, &info);
map_error:
  gst_buffer_unref (buf);
  return NULL;
}
