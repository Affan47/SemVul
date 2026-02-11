gst_rtp_base_depayload_handle_event (GstRTPBaseDepayload * filter,
    GstEvent * event)
{
  gboolean res = TRUE;
  gboolean forward = TRUE;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_FLUSH_STOP:
      gst_segment_init (&filter->segment, GST_FORMAT_UNDEFINED);
      filter->need_newsegment = TRUE;
      filter->priv->next_seqnum = -1;
      break;
    case GST_EVENT_CAPS:
    {
      GstCaps *caps;

      gst_event_parse_caps (event, &caps);

      res = gst_rtp_base_depayload_setcaps (filter, caps);
      forward = FALSE;
      break;
    }
    case GST_EVENT_SEGMENT:
    {
      gst_event_copy_segment (event, &filter->segment);


      forward = FALSE;
      break;
    }
    case GST_EVENT_CUSTOM_DOWNSTREAM:
    {
      GstRTPBaseDepayloadClass *bclass;

      bclass = GST_RTP_BASE_DEPAYLOAD_GET_CLASS (filter);

      if (gst_event_has_name (event, "GstRTPPacketLost")) {


        if (bclass->packet_lost)
          res = bclass->packet_lost (filter, event);
        forward = FALSE;
      }
      break;
    }
    default:
      break;
  }

  if (forward)
    res = gst_pad_push_event (filter->srcpad, event);
  else
    gst_event_unref (event);

  return res;
}
