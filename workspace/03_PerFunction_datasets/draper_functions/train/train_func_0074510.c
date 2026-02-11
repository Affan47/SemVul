gst_rtp_vorbis_depay_class_init (GstRtpVorbisDepayClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;
  GstBaseRTPDepayloadClass *gstbasertpdepayload_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;
  gstbasertpdepayload_class = (GstBaseRTPDepayloadClass *) klass;

  gobject_class->finalize = gst_rtp_vorbis_depay_finalize;

  gstelement_class->change_state = gst_rtp_vorbis_depay_change_state;

  gstbasertpdepayload_class->process = gst_rtp_vorbis_depay_process;
  gstbasertpdepayload_class->set_caps = gst_rtp_vorbis_depay_setcaps;

  GST_DEBUG_CATEGORY_INIT (rtpvorbisdepay_debug, "rtpvorbisdepay", 0,
      "Vorbis RTP Depayloader");
}
