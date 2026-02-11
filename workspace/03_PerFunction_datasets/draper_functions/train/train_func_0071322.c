gst_rtp_bin_reset_sync (GstRtpBin * rtpbin)
{
  GSList *clients, *streams;

  GST_DEBUG_OBJECT (rtpbin, "Reset sync on all clients");

  GST_RTP_BIN_LOCK (rtpbin);
  for (clients = rtpbin->clients; clients; clients = g_slist_next (clients)) {
    GstRtpBinClient *client = (GstRtpBinClient *) clients->data;


    for (streams = client->streams; streams; streams = g_slist_next (streams)) {
      GstRtpBinStream *stream = (GstRtpBinStream *) streams->data;


      stream->have_sync = FALSE;
      stream->rt_delta = 0;
      stream->rtp_delta = 0;
      stream->clock_base = -100 * GST_SECOND;
    }
  }
  GST_RTP_BIN_UNLOCK (rtpbin);
}
