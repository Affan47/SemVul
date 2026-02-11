gst_rtspsrc_prepare_transports (GstRTSPStream * stream, gchar ** transports,
    gint orig_rtpport, gint orig_rtcpport)
{
  GstRTSPSrc *src;
  gint nr_udp, nr_int;
  gchar *next, *p;
  gint rtpport = 0, rtcpport = 0;
  GString *str;

  src = stream->parent;


  if (strstr (*transports, "%%i2"))
    nr_int = 2;
  else if (strstr (*transports, "%%i1"))
    nr_int = 1;
  else
    nr_int = 0;

  if (strstr (*transports, "%%u2"))
    nr_udp = 2;
  else if (strstr (*transports, "%%u1"))
    nr_udp = 1;
  else
    nr_udp = 0;

  if (nr_udp == 0 && nr_int == 0)
    goto done;

  if (nr_udp > 0) {
    if (!orig_rtpport || !orig_rtcpport) {
      if (!gst_rtspsrc_alloc_udp_ports (stream, &rtpport, &rtcpport))
        goto failed;
    } else {
      rtpport = orig_rtpport;
      rtcpport = orig_rtcpport;
    }
  }

  str = g_string_new ("");
  p = *transports;
  while ((next = strstr (p, "%%"))) {
    g_string_append_len (str, p, next - p);
    if (next[2] == 'u') {
      if (next[3] == '1')
        g_string_append_printf (str, "%d", rtpport);
      else if (next[3] == '2')
        g_string_append_printf (str, "%d", rtcpport);
    }
    if (next[2] == 'i') {
      if (next[3] == '1')
        g_string_append_printf (str, "%d", src->free_channel);
      else if (next[3] == '2')
        g_string_append_printf (str, "%d", src->free_channel + 1);
    }

    p = next + 4;
  }

  g_string_append (str, p);

  g_free (*transports);
  *transports = g_string_free (str, FALSE);

done:
  return GST_RTSP_OK;


failed:
  {
    return GST_RTSP_ERROR;
  }
}
