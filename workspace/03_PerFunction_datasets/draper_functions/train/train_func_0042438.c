gst_navseek_sink_event (GstBaseTransform * trans, GstEvent * event)
{
  GstNavSeek *navseek = GST_NAVSEEK (trans);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_EOS:
      GST_OBJECT_LOCK (navseek);
      if (navseek->loop)
        gst_navseek_segseek (navseek);
      GST_OBJECT_UNLOCK (navseek);
      break;
    default:
      break;
  }
  return GST_BASE_TRANSFORM_CLASS (parent_class)->sink_event (trans, event);
}
