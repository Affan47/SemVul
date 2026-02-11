gst_fake_sink_change_state (GstElement * element, GstStateChange transition)
{
  GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
  GstFakeSink *fakesink = GST_FAKE_SINK (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      if (fakesink->state_error == FAKE_SINK_STATE_ERROR_NULL_READY)
        goto error;
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      if (fakesink->state_error == FAKE_SINK_STATE_ERROR_READY_PAUSED)
        goto error;
      fakesink->num_buffers_left = fakesink->num_buffers;
      break;
    case GST_STATE_CHANGE_PAUSED_TO_PLAYING:
      if (fakesink->state_error == FAKE_SINK_STATE_ERROR_PAUSED_PLAYING)
        goto error;
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PLAYING_TO_PAUSED:
      if (fakesink->state_error == FAKE_SINK_STATE_ERROR_PLAYING_PAUSED)
        goto error;
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      if (fakesink->state_error == FAKE_SINK_STATE_ERROR_PAUSED_READY)
        goto error;
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      if (fakesink->state_error == FAKE_SINK_STATE_ERROR_READY_NULL)
        goto error;
      GST_OBJECT_LOCK (fakesink);
      g_free (fakesink->last_message);
      fakesink->last_message = NULL;
      GST_OBJECT_UNLOCK (fakesink);
      break;
    default:
      break;
  }

  return ret;


error:
  GST_ELEMENT_ERROR (element, CORE, STATE_CHANGE, (NULL),
      ("Erroring out on state change as requested"));
  return GST_STATE_CHANGE_FAILURE;
}
