create_stream (GstRtpBinSession * session, guint32 ssrc)
{
  GstElement *buffer, *demux = NULL;
  GstRtpBinStream *stream;
  GstRtpBin *rtpbin;
  GstState target;

  rtpbin = session->bin;

  if (!(buffer = gst_element_factory_make ("gstrtpjitterbuffer", NULL)))
    goto no_jitterbuffer;

  if (!rtpbin->ignore_pt)
    if (!(demux = gst_element_factory_make ("gstrtpptdemux", NULL)))
      goto no_demux;


  stream = g_new0 (GstRtpBinStream, 1);
  stream->ssrc = ssrc;
  stream->bin = rtpbin;
  stream->session = session;
  stream->buffer = buffer;
  stream->demux = demux;

  stream->have_sync = FALSE;
  stream->rt_delta = 0;
  stream->rtp_delta = 0;
  stream->percent = 100;
  stream->clock_base = -100 * GST_SECOND;
  session->streams = g_slist_prepend (session->streams, stream);


  stream->buffer_ptreq_sig = g_signal_connect (buffer, "request-pt-map",
      (GCallback) pt_map_requested, session);
  stream->buffer_ntpstop_sig = g_signal_connect (buffer, "on-npt-stop",
      (GCallback) on_npt_stop, stream);

  g_object_set_data (G_OBJECT (buffer), "GstRTPBin.session", session);
  g_object_set_data (G_OBJECT (buffer), "GstRTPBin.stream", stream);


  g_object_set (buffer, "latency", rtpbin->latency_ms, NULL);
  g_object_set (buffer, "do-lost", rtpbin->do_lost, NULL);
  g_object_set (buffer, "mode", rtpbin->buffer_mode, NULL);

  if (!rtpbin->ignore_pt)
    gst_bin_add (GST_BIN_CAST (rtpbin), demux);
  gst_bin_add (GST_BIN_CAST (rtpbin), buffer);


  if (demux)
    gst_element_link (buffer, demux);

  if (rtpbin->buffering) {
    guint64 last_out;

    GST_INFO_OBJECT (rtpbin,
        "bin is buffering, set jitterbuffer as not active");
    g_signal_emit_by_name (buffer, "set-active", FALSE, (gint64) 0, &last_out);
  }


  GST_OBJECT_LOCK (rtpbin);
  target = GST_STATE_TARGET (rtpbin);
  GST_OBJECT_UNLOCK (rtpbin);


  if (demux)
    gst_element_set_state (demux, target);

  gst_element_set_state (buffer, target);

  return stream;


no_jitterbuffer:
  {
    g_warning ("gstrtpbin: could not create gstrtpjitterbuffer element");
    return NULL;
  }
no_demux:
  {
    gst_object_unref (buffer);
    g_warning ("gstrtpbin: could not create gstrtpptdemux element");
    return NULL;
  }
}
