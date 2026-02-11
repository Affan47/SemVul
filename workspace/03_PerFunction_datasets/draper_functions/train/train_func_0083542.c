gst_rtp_ssrc_demux_src_event (GstPad * pad, GstEvent * event)
{
  GstRtpSsrcDemux *demux;
  const GstStructure *s;

  demux = GST_RTP_SSRC_DEMUX (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CUSTOM_UPSTREAM:
    case GST_EVENT_CUSTOM_BOTH:
    case GST_EVENT_CUSTOM_BOTH_OOB:
      s = gst_event_get_structure (event);
      if (s && !gst_structure_has_field (s, "ssrc")) {
        GSList *walk;

        for (walk = demux->srcpads; walk; walk = g_slist_next (walk)) {
          GstRtpSsrcDemuxPad *dpad = (GstRtpSsrcDemuxPad *) walk->data;

          if (dpad->rtp_pad == pad || dpad->rtcp_pad == pad) {
            event =
                GST_EVENT_CAST (gst_mini_object_make_writable
                (GST_MINI_OBJECT_CAST (event)));
            gst_structure_set (event->structure, "ssrc", G_TYPE_UINT,
                dpad->ssrc, NULL);
            break;
          }
        }
      }
      break;
    default:
      break;
  }

  gst_object_unref (demux);

  return gst_pad_event_default (pad, event);
}
