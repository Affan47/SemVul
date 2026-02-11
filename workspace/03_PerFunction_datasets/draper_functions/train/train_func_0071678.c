gst_ogg_demux_seek_back_after_push_duration_check_unlock (GstOggDemux * ogg)
{
  GstEvent *event;


  event = ogg->push_mode_seek_delayed_event;
  ogg->push_mode_seek_delayed_event = NULL;

  ogg->push_state = PUSH_PLAYING;

  GST_PUSH_UNLOCK (ogg);

  if (event) {

    gst_ogg_demux_perform_seek_push (ogg, event);
  } else {

    GST_INFO_OBJECT (ogg, "Seeking back to 0 after duration check");
    event = gst_event_new_seek (1.0, GST_FORMAT_BYTES,
        GST_SEEK_FLAG_ACCURATE | GST_SEEK_FLAG_FLUSH,
        GST_SEEK_TYPE_SET, 1, GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE);
    if (!gst_pad_push_event (ogg->sinkpad, event)) {
      GST_WARNING_OBJECT (ogg, "Failed seeking back to start");
      return GST_FLOW_ERROR;
    }
  }

  return GST_FLOW_OK;
}
