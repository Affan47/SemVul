gst_rtspsrc_parse_rtpinfo (GstRTSPSrc * src, gchar * rtpinfo)
{
  gchar **infos;
  gint i, j;

  GST_DEBUG_OBJECT (src, "parsing RTP-Info %s", rtpinfo);

  infos = g_strsplit (rtpinfo, ",", 0);
  for (i = 0; infos[i]; i++) {
    gchar **fields;
    GstRTSPStream *stream;
    gint32 seqbase;
    gint64 timebase;

    GST_DEBUG_OBJECT (src, "parsing info %s", infos[i]);


    stream = NULL;
    seqbase = -1;
    timebase = -1;


    fields = g_strsplit (infos[i], ";", 0);
    for (j = 0; fields[j]; j++) {
      GST_DEBUG_OBJECT (src, "parsing field %s", fields[j]);

      fields[j] = g_strchug (fields[j]);
      if (g_str_has_prefix (fields[j], "url=")) {

        stream =
            find_stream (src, (fields[j] + 4), (gpointer) find_stream_by_setup);
      } else if (g_str_has_prefix (fields[j], "seq=")) {
        seqbase = atoi (fields[j] + 4);
      } else if (g_str_has_prefix (fields[j], "rtptime=")) {
        timebase = g_ascii_strtoll (fields[j] + 8, NULL, 10);
      }
    }
    g_strfreev (fields);

    if (stream != NULL) {
      GST_DEBUG_OBJECT (src,
          "found stream %p, setting: seqbase %d, timebase %" G_GINT64_FORMAT,
          stream, seqbase, timebase);


      stream->seqbase = seqbase;
      stream->timebase = timebase;
    }
  }
  g_strfreev (infos);

  return TRUE;
}
