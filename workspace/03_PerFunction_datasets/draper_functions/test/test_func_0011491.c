gst_level_sink_event (GstBaseTransform * trans, GstEvent * event)
{
  if (GST_EVENT_TYPE (event) == GST_EVENT_EOS) {
    GstLevel *filter = GST_LEVEL (trans);

    gst_level_post_message (filter);
  }

  return GST_BASE_TRANSFORM_CLASS (parent_class)->sink_event (trans, event);
}
