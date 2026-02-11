gst_a2dp_sink_change_state (GstElement * element, GstStateChange transition)
{
  GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
  GstA2dpSink *self = GST_A2DP_SINK (element);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      self->taglist = gst_tag_list_new_empty ();

      gst_a2dp_sink_init_fakesink (self);
      break;

    case GST_STATE_CHANGE_NULL_TO_READY:
      self->sink_is_in_bin = FALSE;
      self->sink =
          GST_AVDTP_SINK (gst_element_factory_make ("avdtpsink", "avdtpsink"));
      if (self->sink == NULL) {
        GST_WARNING_OBJECT (self, "failed to create avdtpsink");
        return GST_STATE_CHANGE_FAILURE;
      }

      if (self->device != NULL)
        gst_avdtp_sink_set_device (self->sink, self->device);

      if (self->transport != NULL)
        gst_avdtp_sink_set_transport (self->sink, self->transport);

      g_object_set (G_OBJECT (self->sink), "auto-connect",
          self->autoconnect, NULL);

      ret = gst_element_set_state (GST_ELEMENT (self->sink), GST_STATE_READY);
      break;
    default:
      break;
  }

  if (ret == GST_STATE_CHANGE_FAILURE)
    return ret;

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      if (self->taglist) {
        gst_tag_list_unref (self->taglist);
        self->taglist = NULL;
      }
      if (self->segment_event != NULL) {
        gst_event_unref (self->segment_event);
        self->segment_event = NULL;
      }
      gst_a2dp_sink_remove_fakesink (self);
      break;

    case GST_STATE_CHANGE_READY_TO_NULL:
      if (self->sink_is_in_bin) {
        if (!gst_bin_remove (GST_BIN (self), GST_ELEMENT (self->sink)))
          GST_WARNING_OBJECT (self, "Failed to remove " "avdtpsink from bin");
      } else if (self->sink != NULL) {
        gst_element_set_state (GST_ELEMENT (self->sink), GST_STATE_NULL);
        g_object_unref (G_OBJECT (self->sink));
      }

      self->sink = NULL;

      gst_a2dp_sink_remove_dynamic_elements (self);
      break;
    default:
      break;
  }

  return ret;
}
