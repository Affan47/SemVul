gst_rtp_ssrc_demux_class_init (GstRtpSsrcDemuxClass * klass)
{
  GObjectClass *gobject_klass;
  GstElementClass *gstelement_klass;
  GstRtpSsrcDemuxClass *gstrtpssrcdemux_klass;

  gobject_klass = (GObjectClass *) klass;
  gstelement_klass = (GstElementClass *) klass;
  gstrtpssrcdemux_klass = (GstRtpSsrcDemuxClass *) klass;

  gobject_klass->dispose = gst_rtp_ssrc_demux_dispose;
  gobject_klass->finalize = gst_rtp_ssrc_demux_finalize;


  gst_rtp_ssrc_demux_signals[SIGNAL_NEW_SSRC_PAD] =
      g_signal_new ("new-ssrc-pad",
      G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
      G_STRUCT_OFFSET (GstRtpSsrcDemuxClass, new_ssrc_pad),
      NULL, NULL, gst_rtp_bin_marshal_VOID__UINT_OBJECT,
      G_TYPE_NONE, 2, G_TYPE_UINT, GST_TYPE_PAD);


  gst_rtp_ssrc_demux_signals[SIGNAL_REMOVED_SSRC_PAD] =
      g_signal_new ("removed-ssrc-pad",
      G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
      G_STRUCT_OFFSET (GstRtpSsrcDemuxClass, removed_ssrc_pad),
      NULL, NULL, gst_rtp_bin_marshal_VOID__UINT_OBJECT,
      G_TYPE_NONE, 2, G_TYPE_UINT, GST_TYPE_PAD);


  gst_rtp_ssrc_demux_signals[SIGNAL_CLEAR_SSRC] =
      g_signal_new ("clear-ssrc",
      G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
      G_STRUCT_OFFSET (GstRtpSsrcDemuxClass, clear_ssrc),
      NULL, NULL, gst_rtp_bin_marshal_VOID__UINT, G_TYPE_NONE, 1, G_TYPE_UINT);

  gstelement_klass->change_state =
      GST_DEBUG_FUNCPTR (gst_rtp_ssrc_demux_change_state);
  gstrtpssrcdemux_klass->clear_ssrc =
      GST_DEBUG_FUNCPTR (gst_rtp_ssrc_demux_clear_ssrc);

  GST_DEBUG_CATEGORY_INIT (gst_rtp_ssrc_demux_debug,
      "rtpssrcdemux", 0, "RTP SSRC demuxer");
}
