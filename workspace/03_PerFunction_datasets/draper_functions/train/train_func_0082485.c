gst_event_new_caps (GstCaps * caps)
{
  GstEvent *event;

  g_return_val_if_fail (caps != NULL, NULL);
  g_return_val_if_fail (gst_caps_is_fixed (caps), NULL);

  GST_CAT_INFO (GST_CAT_EVENT, "creating caps event %" GST_PTR_FORMAT, caps);

  event = gst_event_new_custom (GST_EVENT_CAPS,
      gst_structure_new_id (GST_QUARK (EVENT_CAPS),
          GST_QUARK (CAPS), GST_TYPE_CAPS, caps, NULL));

  return event;
}
