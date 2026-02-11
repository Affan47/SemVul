gst_rtp_dtmf_mux_src_event (GstRTPMux * rtp_mux, GstEvent * event)
{
  if (GST_EVENT_TYPE (event) == GST_EVENT_CUSTOM_UPSTREAM) {
    const GstStructure *s = gst_event_get_structure (event);

    if (s && gst_structure_has_name (s, "dtmf-event")) {
      GST_OBJECT_LOCK (rtp_mux);
      if (GST_CLOCK_TIME_IS_VALID (rtp_mux->last_stop)) {
        event = (GstEvent *)
            gst_mini_object_make_writable (GST_MINI_OBJECT_CAST (event));
        s = gst_event_get_structure (event);
        gst_structure_set ((GstStructure *) s,
            "last-stop", G_TYPE_UINT64, rtp_mux->last_stop, NULL);
      }
      GST_OBJECT_UNLOCK (rtp_mux);
    }
  }

  return GST_RTP_MUX_CLASS (gst_rtp_dtmf_mux_parent_class)->src_event (rtp_mux,
      event);
}
