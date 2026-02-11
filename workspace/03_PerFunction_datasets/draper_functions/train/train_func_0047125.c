do_handle_sync (GstRtpJitterBuffer * jitterbuffer)
{
  GstRtpJitterBufferPrivate *priv;
  guint64 base_rtptime, base_time;
  guint32 clock_rate;
  guint64 last_rtptime;
  guint64 clock_base;
  guint64 ext_rtptime, diff;
  gboolean drop = FALSE;

  priv = jitterbuffer->priv;


  rtp_jitter_buffer_get_sync (priv->jbuf, &base_rtptime, &base_time,
      &clock_rate, &last_rtptime);

  clock_base = priv->clock_base;
  ext_rtptime = priv->ext_rtptime;

  GST_DEBUG_OBJECT (jitterbuffer, "ext SR %" G_GUINT64_FORMAT ", base %"
      G_GUINT64_FORMAT ", clock-rate %" G_GUINT32_FORMAT
      ", clock-base %" G_GUINT64_FORMAT ", last-rtptime %" G_GUINT64_FORMAT,
      ext_rtptime, base_rtptime, clock_rate, clock_base, last_rtptime);

  if (base_rtptime == -1 || clock_rate == -1 || base_time == -1) {
    GST_DEBUG_OBJECT (jitterbuffer, "dropping, no RTP values");
    drop = TRUE;
  } else {

    if (base_rtptime > ext_rtptime) {
      GST_DEBUG_OBJECT (jitterbuffer, "dropping, older than base time");
      drop = TRUE;
    } else {


      if (ext_rtptime > last_rtptime) {

        diff = ext_rtptime - last_rtptime;

        if (diff > clock_rate) {
          GST_DEBUG_OBJECT (jitterbuffer, "too far ahead");


          ext_rtptime = -1;
        }
        GST_DEBUG_OBJECT (jitterbuffer, "ext last %" G_GUINT64_FORMAT ", diff %"
            G_GUINT64_FORMAT, last_rtptime, diff);
      }
    }
  }

  if (!drop) {
    GstStructure *s;

    s = gst_structure_new ("application/x-rtp-sync",
        "base-rtptime", G_TYPE_UINT64, base_rtptime,
        "base-time", G_TYPE_UINT64, base_time,
        "clock-rate", G_TYPE_UINT, clock_rate,
        "clock-base", G_TYPE_UINT64, clock_base,
        "sr-ext-rtptime", G_TYPE_UINT64, ext_rtptime,
        "sr-buffer", GST_TYPE_BUFFER, priv->last_sr, NULL);

    GST_DEBUG_OBJECT (jitterbuffer, "signaling sync");
    gst_buffer_replace (&priv->last_sr, NULL);
    JBUF_UNLOCK (priv);
    g_signal_emit (jitterbuffer,
        gst_rtp_jitter_buffer_signals[SIGNAL_HANDLE_SYNC], 0, s);
    JBUF_LOCK (priv);
    gst_structure_free (s);
  } else {
    GST_DEBUG_OBJECT (jitterbuffer, "dropping RTCP packet");
  }
}
