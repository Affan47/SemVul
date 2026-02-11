gst_base_src_change_state (GstElement * element, GstStateChange transition)
{
  GstBaseSrc *basesrc;
  GstStateChangeReturn result;
  gboolean no_preroll = FALSE;

  basesrc = GST_BASE_SRC (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      no_preroll = gst_base_src_is_live (basesrc);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_PLAYING:
      GST_DEBUG_OBJECT (basesrc, "PAUSED->PLAYING");
      if (gst_base_src_is_live (basesrc)) {

        gst_base_src_set_playing (basesrc, TRUE);
      }
      break;
    default:
      break;
  }

  if ((result =
          GST_ELEMENT_CLASS (parent_class)->change_state (element,
              transition)) == GST_STATE_CHANGE_FAILURE)
    goto failure;

  switch (transition) {
    case GST_STATE_CHANGE_PLAYING_TO_PAUSED:
      GST_DEBUG_OBJECT (basesrc, "PLAYING->PAUSED");
      if (gst_base_src_is_live (basesrc)) {

        gst_base_src_set_playing (basesrc, FALSE);
        no_preroll = TRUE;
      }
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
    {
      GstEvent **event_p, *event;


      if (!basesrc->priv->last_sent_eos) {
        GST_DEBUG_OBJECT (basesrc, "Sending EOS event");
        event = gst_event_new_eos ();
        gst_event_set_seqnum (event, basesrc->priv->seqnum);
        gst_pad_push_event (basesrc->srcpad, event);
        basesrc->priv->last_sent_eos = TRUE;
      }
      g_atomic_int_set (&basesrc->priv->pending_eos, FALSE);
      event_p = &basesrc->data.ABI.pending_seek;
      gst_event_replace (event_p, NULL);
      event_p = &basesrc->priv->close_segment;
      gst_event_replace (event_p, NULL);
      event_p = &basesrc->priv->start_segment;
      gst_event_replace (event_p, NULL);
      break;
    }
    case GST_STATE_CHANGE_READY_TO_NULL:
      break;
    default:
      break;
  }

  if (no_preroll && result == GST_STATE_CHANGE_SUCCESS)
    result = GST_STATE_CHANGE_NO_PREROLL;

  return result;


failure:
  {
    GST_DEBUG_OBJECT (basesrc, "parent failed state change");
    return result;
  }
}
