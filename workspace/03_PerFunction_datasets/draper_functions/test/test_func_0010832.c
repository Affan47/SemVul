gst_opus_header_create_caps_from_headers (GstCaps ** caps, GSList ** headers,
    GstBuffer * buf1, GstBuffer * buf2)
{
  int n_streams, family;
  gboolean multistream;
  GstMapInfo map;
  guint8 *data;

  g_return_if_fail (caps);
  g_return_if_fail (headers && !*headers);
  g_return_if_fail (gst_buffer_get_size (buf1) >= 19);

  gst_buffer_map (buf1, &map, GST_MAP_READ);
  data = map.data;


  family = data[18];
  if (family == 0) {
    n_streams = 1;
  } else {

    if (map.size >= 20)
      n_streams = data[19];
    else {
      g_warning ("family > 0 but header buffer size < 20");
      gst_buffer_unmap (buf1, &map);
      return;
    }
  }

  gst_buffer_unmap (buf1, &map);


  multistream = n_streams > 1;
  *caps = gst_caps_new_simple ("audio/x-opus",
      "multistream", G_TYPE_BOOLEAN, multistream, NULL);
  *caps = _gst_caps_set_buffer_array (*caps, "streamheader", buf1, buf2, NULL);

  *headers = g_slist_prepend (*headers, buf2);
  *headers = g_slist_prepend (*headers, buf1);
}
