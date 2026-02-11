gst_rtp_base_depayload_class_init (GstRTPBaseDepayloadClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gstelement_class = (GstElementClass *) klass;
  parent_class = g_type_class_peek_parent (klass);

  g_type_class_add_private (klass, sizeof (GstRTPBaseDepayloadPrivate));

  gobject_class->finalize = gst_rtp_base_depayload_finalize;
  gobject_class->set_property = gst_rtp_base_depayload_set_property;
  gobject_class->get_property = gst_rtp_base_depayload_get_property;

  gstelement_class->change_state = gst_rtp_base_depayload_change_state;

  klass->packet_lost = gst_rtp_base_depayload_packet_lost;
  klass->handle_event = gst_rtp_base_depayload_handle_event;

  GST_DEBUG_CATEGORY_INIT (rtpbasedepayload_debug, "rtpbasedepayload", 0,
      "Base class for RTP Depayloaders");
}
